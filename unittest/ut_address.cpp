#include <gtest/gtest.h>

#include "net/address.hpp"

TEST(ut_address, default) {
    miu::net::address addr;
    EXPECT_EQ(nullptr, addr.raw());
    EXPECT_EQ(0U, addr.len());
}
