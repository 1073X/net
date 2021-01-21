#include <gtest/gtest.h>

#include "net/address.hpp"
#include "source/lib/udsaddr.hpp"

TEST(ut_address, default) {
    miu::net::address addr;
    EXPECT_EQ(nullptr, addr.raw());
    EXPECT_EQ(0U, addr.len());
}

TEST(ut_address, uds) {
    miu::net::udsaddr addr { "ut_address" };
    EXPECT_NE(nullptr, addr.raw());
    EXPECT_EQ(sizeof(sockaddr_un), addr.len());
}
