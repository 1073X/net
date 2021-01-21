#include <gtest/gtest.h>

#include "net/tempfs.hpp"

TEST(ut_tempfs, path) { EXPECT_EQ("/tmp/miu", miu::net::tempfs.path()); }
