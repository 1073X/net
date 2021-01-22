
#include "net/socket.hpp"

#include <errno.h>
#include <string.h>        // strerror
#include <sys/socket.h>    // socket
#include <sys/types.h>     // getsockopt

#include <com/system_warn.hpp>

namespace miu::net {

socket::socket(int32_t family, int32_t type)
    : _raw(::socket(family, type, 0)) {}

bool
socket::reuse_addr() const {
    int32_t val;
    socklen_t len = sizeof(val);
    getsockopt(_raw, SOL_SOCKET, SO_REUSEADDR, (char*)&val, &len);
    return val != 0;
}

bool
socket::bind(address const& addr) {
    auto err = ::bind(_raw, addr.raw(), addr.len());
    if (err) {
        SYSTEM_WARN("::bind", addr.str(), errno, strerror(errno));
    }
    return !err;
}

}    // namespace miu::net
