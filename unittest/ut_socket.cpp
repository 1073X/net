#include <gtest/gtest.h>

#include "net/socket.hpp"

TEST(ut_socket, default) {
    miu::net::socket sock;
    EXPECT_EQ(-1, sock.raw());
    EXPECT_FALSE(sock);
    EXPECT_TRUE(!sock);
}
