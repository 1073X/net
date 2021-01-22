#pragma once

#include <string_view>

#include "socket.hpp"

namespace miu::net {

struct udsock {
    static socket create_server(std::string_view);
    static socket create_client(std::string_view);
};

}    // namespace miu::net
