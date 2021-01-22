
#include "net/tcpsock.hpp"

#include "tcpaddr.hpp"

namespace miu::net {

socket
tcpsock::create_server(std::string_view interface, std::string_view service) {
    auto sock = socket { AF_INET, SOCK_STREAM };
    if (sock) {
        sock.set_reuseaddr(true);
        tcpaddr addr { interface, service };
        if (sock.bind(addr)) {
            if (sock.listen()) {
                return sock;
            }
        }
    }

    return {};
}

socket
tcpsock::create_client(std::string_view host, std::string_view port) {
    auto sock = socket { AF_INET, SOCK_STREAM };
    if (sock) {
        tcpaddr addr { host, port };
        if (sock.connect(addr)) {
            return sock;
        }
    }

    return {};
}

}    // namespace miu::net
