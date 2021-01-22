#include <gtest/gtest.h>

#include "net/socket.hpp"
#include "net/tempfs.hpp"
#include "net/udsock.hpp"
#include "source/lib/udsaddr.hpp"

namespace fs = std::filesystem;
using miu::net::tempfs;

TEST(ut_socket, default) {
    miu::net::socket sock;
    EXPECT_EQ(-1, sock.raw());
    EXPECT_FALSE(sock);
    EXPECT_TRUE(!sock);
}

TEST(ut_socket, udsock_server) {
    auto path = tempfs.path();
    tempfs.reset(".");

    auto sock = miu::net::udsock::create_server("ut_socket");
    EXPECT_TRUE(sock);
    EXPECT_FALSE(sock.reuse_addr());

    EXPECT_TRUE(tempfs.exists("ut_socket.uds"));
    auto exp = fs::perms::owner_read | fs::perms::owner_write | fs::perms::owner_exec
               | fs::perms::group_read | fs::perms::group_write | fs::perms::group_exec;
    auto status = fs::status(tempfs.join("ut_socket.uds"));
    EXPECT_EQ(exp, status.permissions());

    // cann't be duplicated
    EXPECT_FALSE(miu::net::udsock::create_server("ut_socket"));

    tempfs.remove("ut_socket.uds");
    tempfs.reset(path.string());
}
