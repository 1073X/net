#pragma once

#include "socket.hpp"

namespace miu::net {

struct tcpsock {
    static socket create_server(std::string_view interface, std::string_view service);
};

}    // namespace miu::net
