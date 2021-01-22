
#include "net/udsock.hpp"

#include "udsaddr.hpp"

namespace fs = std::filesystem;

namespace miu::net {

socket
udsock::create_server(std::string_view name) {
    auto sock = socket(AF_UNIX, SOCK_STREAM);
    if (sock) {
        udsaddr addr { name };
        if (sock.bind(addr)) {
            auto perm = fs::perms::owner_read | fs::perms::owner_write | fs::perms::owner_exec
                        | fs::perms::group_read | fs::perms::group_write | fs::perms::group_exec;

            std::error_code ec;
            fs::permissions(addr.str(), perm, ec);
            if (!ec) {
                return sock;
            }
        }
    }

    return {};
}

}    // namespace miu::net
