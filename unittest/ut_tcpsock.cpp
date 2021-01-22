#include <gtest/gtest.h>

#include <future>
#include <thread>

#include "net/tcpsock.hpp"

using miu::net::tcpsock;

TEST(ut_tcpsock, server) {
    auto sock = tcpsock::create_server("0.0.0.0", "15000");
    EXPECT_TRUE(sock);
    EXPECT_EQ(SOCK_STREAM, sock.type());
    EXPECT_TRUE(sock.reuseaddr());
    EXPECT_TRUE(sock.acceptconn());
    EXPECT_FALSE(sock.nonblock());
}

TEST(ut_tcpsock, client) {
    // failed to connect server
    EXPECT_FALSE(tcpsock::create_client("127.0.0.1", "15000"));

    std::promise<bool> ready;
    std::thread thrd([&]() {
        auto sock = tcpsock::create_server("0.0.0.0", "15000");
        ready.set_value(true);

        auto cli = sock.accept();
        EXPECT_TRUE(cli);

        // send a few bytes
        EXPECT_EQ(4, cli.send("def", 4));
    });
    ready.get_future().get();    // waiting for server get ready for accept

    auto sock = tcpsock::create_client("127.0.0.1", "15000");
    EXPECT_TRUE(sock);

    // recv
    char buf[8] {};
    EXPECT_EQ(4U, sock.recv(buf, sizeof(buf)));
    EXPECT_STREQ("def", buf);

    thrd.join();
}

TEST(ut_tcpsock, nodelay) {
    auto sock = tcpsock::create_server("0.0.0.0", "15000");
    EXPECT_FALSE(sock.nodelay());
    sock.set_nodelay(true);
    EXPECT_TRUE(sock.nodelay());
}

TEST(ut_tcpsock, sndbuf) {
    auto sock = tcpsock::create_server("0.0.0.0", "15000");

    auto sndbuf = sock.sndbuf();
    sock.set_sndbuf(sndbuf * 2);
    EXPECT_EQ(sndbuf * 4, sock.sndbuf());
}

TEST(ut_tcpsock, rcvbuf) {
    auto sock = tcpsock::create_server("0.0.0.0", "15000");

    auto rcvbuf = sock.rcvbuf();
    sock.set_rcvbuf(rcvbuf * 2);
    EXPECT_EQ(rcvbuf * 4, sock.rcvbuf());
}
