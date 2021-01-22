#pragma once

#include <arpa/inet.h>
#include <netdb.h>     // getaddrinfo
#include <string.h>    // memset

#include "net/socket.hpp"

namespace miu::net {

class tcpaddr : public address {
  public:
    tcpaddr(std::string_view interface, std::string_view service) {
        addrinfo hint;
        memset(&hint, 0, sizeof(hint));
        hint.ai_family = AF_UNSPEC;
        hint.ai_socktype = SOCK_STREAM;

        if (::getaddrinfo(interface.data(), service.data(), &hint, &_info)) {
            _info = nullptr;
        }
    }

    ~tcpaddr() override { freeaddrinfo(_info); }

    sockaddr const* raw() const override {
        sockaddr const* addr = nullptr;
        if (_info) {
            addr = _info->ai_addr;
        }
        return addr;
    }

    int32_t family() const override {
        int32_t family = AF_UNSPEC;
        if (_info) {
            family = _info->ai_family;
        }
        return family;
    }

    uint32_t len() const override {
        uint32_t len = 0;
        if (_info) {
            len = _info->ai_addrlen;
        }
        return len;
    }

    std::string str() const override {
        std::string str;
        if (_info) {
            auto addr_in = (sockaddr_in const*)raw();
            str = inet_ntoa(addr_in->sin_addr);
            auto port = htons(addr_in->sin_port);
            str += ":" + std::to_string(port);
        }
        return str;
    }

  private:
    addrinfo* _info;
};

}    // namespace miu::net
