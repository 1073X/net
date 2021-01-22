#pragma once

#include "socket.hpp"

namespace miu::net {

struct tcpsock {
    static socket create_server(std::string_view interface, std::string_view service);
    static socket create_client(std::string_view host, std::string_view port);
};

}    // namespace miu::net
