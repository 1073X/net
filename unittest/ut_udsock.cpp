#include <gtest/gtest.h>

#include <future>
#include <thread>

#include "net/udsock.hpp"
#include "source/lib/udsaddr.hpp"

using miu::net::udsock;

TEST(ut_udsock, server) {
    auto sock = udsock::create_server("ut_udsock");
    EXPECT_TRUE(sock);
    EXPECT_FALSE(sock.reuseaddr());
    EXPECT_TRUE(sock.acceptconn());
    EXPECT_FALSE(sock.nonblock());

    // cann't be duplicated
    EXPECT_FALSE(udsock::create_server("ut_udsock"));

    // however it is ok to reopen
    { auto sock2 = std::move(sock); }
    EXPECT_TRUE(udsock::create_server("ut_udsock"));
}

TEST(ut_udsock, timeout) {
    auto sock = udsock::create_server("ut_udsock");

    EXPECT_EQ(miu::com::microseconds::zero(), sock.timeout());

    sock.set_timeout(miu::com::microseconds(12000));
    EXPECT_EQ(12000, sock.timeout().count());

    EXPECT_FALSE(sock.accept());    // should timeout
}

TEST(ut_udsock, client) {
    // failed to connect server
    EXPECT_FALSE(udsock::create_client("ut_udsock"));

    std::promise<bool> ready;
    std::thread thrd([&]() {
        auto sock = udsock::create_server("ut_udsock");
        ready.set_value(true);

        auto cli = sock.accept();
        EXPECT_TRUE(cli);

        // send a few bytes
        EXPECT_EQ(4, cli.send("def", 4));
    });
    ready.get_future().get();    // waiting for server get ready for accept

    auto sock = udsock::create_client("ut_udsock");
    EXPECT_TRUE(sock);

    // recv
    char buf[8] {};
    EXPECT_EQ(4U, sock.recv(buf, sizeof(buf)));
    EXPECT_STREQ("def", buf);

    thrd.join();
}

TEST(ut_udsock, recv_failed) {
    std::promise<bool> ready;
    std::thread thrd([&]() {
        auto sock = udsock::create_server("ut_udsock");
        ready.set_value(true);
        sock.accept();
    });
    ready.get_future().get();    // waiting for server get ready for accept

    auto sock = udsock::create_client("ut_udsock");
    thrd.join();    // waiting for server stop

    char buf[8] {};
    EXPECT_GE(0, sock.recv(buf, sizeof(buf)));
}

TEST(ut_udsock, send_failed) {
    std::promise<bool> ready;
    std::thread thrd([&]() {
        auto sock = udsock::create_server("ut_udsock");
        ready.set_value(true);
        sock.accept();
    });
    ready.get_future().get();    // waiting for server get ready for accept

    auto sock = udsock::create_client("ut_udsock");
    thrd.join();    // waiting for server stop

    EXPECT_GE(0, sock.send("abc", 4));
}

