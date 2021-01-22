#pragma once

#include <cstdint>

#include "address.hpp"

namespace miu::net {

class socket {
  public:
    socket() = default;
    socket(int32_t family, int32_t type);

    auto operator!() const { return _raw < 0; }
    operator bool() const { return !operator!(); }

    auto raw() const { return _raw; }

    bool reuse_addr() const;

    bool bind(address const&);

  private:
    int32_t _raw { -1 };
};

}    // namespace miu::net
