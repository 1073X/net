#include <gtest/gtest.h>

#include "net/address.hpp"
#include "source/lib/udsaddr.hpp"

TEST(ut_address, default) {
    miu::net::address addr;
    EXPECT_EQ(nullptr, addr.raw());
    EXPECT_EQ(AF_UNSPEC, addr.family());
    EXPECT_EQ(0U, addr.len());
    EXPECT_EQ("unknown address", addr.str());
}

TEST(ut_address, udsaddr) {
    miu::net::udsaddr addr { "ut_address" };
    EXPECT_NE(nullptr, addr.raw());
    EXPECT_EQ(AF_UNIX, addr.family());
    EXPECT_EQ(sizeof(sockaddr_un), addr.len());
    EXPECT_EQ("ut_address", addr.str());
}
