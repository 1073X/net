#pragma once

#include <netinet/ip.h>    // sockaddr

#include <string>

namespace miu::net {

class address {
  public:
    virtual ~address() = default;
    virtual sockaddr const* raw() const { return nullptr; }
    virtual int32_t family() const { return AF_UNSPEC; }
    virtual uint32_t len() const { return 0; }
    virtual std::string str() const { return "unknown address"; }
};

}    // namespace miu::net
