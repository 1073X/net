#pragma once

#include <cstdint>

namespace miu::net {

class socket {
  public:
    socket() = default;

    auto operator!() const { return _raw < 0; }
    operator bool() const { return !operator!(); }

    auto raw() const { return _raw; }

  private:
    int32_t _raw { -1 };
};

}    // namespace miu::net
