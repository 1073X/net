#pragma once

#include <sys/un.h>    // sockaddr_un

#include "net/address.hpp"

namespace miu::net {

class udsaddr : public address {
  public:
    udsaddr(std::string_view name) {
        _raw.sun_family = AF_UNIX;
        strncpy(_raw.sun_path + 1, name.data(), sizeof(_raw.sun_path));
    }

    sockaddr const* raw() const override { return (sockaddr const*)&_raw; };
    int32_t family() const override { return _raw.sun_family; }
    uint32_t len() const override { return sizeof(_raw); }

    std::string str() const override { return _raw.sun_path + 1; }

  private:
    sockaddr_un _raw {};
};

}    // namespace miu::net
