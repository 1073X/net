#include <gtest/gtest.h>

#include "net/socket.hpp"

TEST(ut_socket, default) {
    miu::net::socket sock;
    EXPECT_EQ(-1, sock.raw());
    EXPECT_FALSE(sock);
    EXPECT_TRUE(!sock);
}

TEST(ut_socket, move) {
    miu::net::socket sock { 99 };

    miu::net::socket sock2 { std::move(sock) };
    EXPECT_EQ(99, sock2.raw());
    EXPECT_EQ(-1, sock.raw());    // NOLINT: testing move

    miu::net::socket sock3 { 100 };
    sock2 = std::move(sock3);
    EXPECT_EQ(100, sock2.raw());
    EXPECT_EQ(99, sock3.raw());    // NOLINT: testing move
}
