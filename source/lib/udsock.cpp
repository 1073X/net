
#include "net/udsock.hpp"

#include "udaddr.hpp"

namespace miu::net {

socket
udsock::create_server(std::string_view name) {
    auto sock = socket(AF_UNIX, SOCK_STREAM);
    if (sock) {
        if (sock.bind(udaddr { name })) {
            if (sock.listen()) {
                return sock;
            }
        }
    }

    return {};
}

socket
udsock::create_client(std::string_view name) {
    auto sock = socket(AF_UNIX, SOCK_STREAM);
    if (sock) {
        if (sock.connect(udaddr { name })) {
            return sock;
        }
    }

    return {};
}

}    // namespace miu::net
