#pragma once

#include <netinet/ip.h>    // sockaddr

namespace miu::net {

class address {
  public:
    virtual ~address() = default;
    virtual sockaddr const* raw() const { return nullptr; }
    virtual uint32_t len() const { return 0; }
};

}    // namespace miu::net
