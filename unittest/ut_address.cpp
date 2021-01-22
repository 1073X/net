#include <gtest/gtest.h>

#include "net/address.hpp"
#include "source/lib/tcpaddr.hpp"
#include "source/lib/udaddr.hpp"

TEST(ut_address, default) {
    miu::net::address addr;
    EXPECT_EQ(nullptr, addr.raw());
    EXPECT_EQ(AF_UNSPEC, addr.family());
    EXPECT_EQ(0U, addr.len());
    EXPECT_EQ("unknown address", addr.str());
}

TEST(ut_address, udaddr) {
    miu::net::udaddr addr { "ut_address" };
    EXPECT_NE(nullptr, addr.raw());
    EXPECT_EQ(AF_UNIX, addr.family());
    EXPECT_EQ(sizeof(sockaddr_un), addr.len());
    EXPECT_EQ("ut_address", addr.str());
}

TEST(ut_address, tcpaddr) {
    miu::net::tcpaddr addr { "127.0.0.1", "123" };
    EXPECT_NE(nullptr, addr.raw());
    EXPECT_EQ(AF_INET, addr.family());
    EXPECT_LT(0, addr.len());
    EXPECT_EQ("127.0.0.1:123", addr.str());
}
