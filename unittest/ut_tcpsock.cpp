#include <gtest/gtest.h>

#include "net/tcpsock.hpp"

TEST(ut_tcpsock, server) {
    auto sock = miu::net::tcpsock::create_server("0.0.0.0", "15000");
    EXPECT_TRUE(sock);
    EXPECT_EQ(SOCK_STREAM, sock.type());
    EXPECT_TRUE(sock.reuseaddr());
    EXPECT_TRUE(sock.acceptconn());
    EXPECT_FALSE(sock.nonblock());
}
