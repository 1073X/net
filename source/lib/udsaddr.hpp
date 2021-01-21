#pragma once

#include <sys/un.h>    // sockaddr_un

#include "net/address.hpp"

namespace miu::net {

class udsaddr : public address {
  public:
    udsaddr(std::string_view name) {}

    sockaddr const* raw() const override { return (sockaddr const*)&_raw; };
    uint32_t len() const override { return sizeof(_raw); }

  private:
    sockaddr_un _raw {};
};

}    // namespace miu::net
