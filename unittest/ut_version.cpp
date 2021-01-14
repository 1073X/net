#include <gtest/gtest.h>

#include <iostream>

namespace miu::net {
extern std::string_view version();
extern std::string_view build_info();
}    // namespace miu::net

TEST(ut_version, version) {
    std::cout << miu::net::version() << std::endl;
    std::cout << miu::net::build_info() << std::endl;
}
