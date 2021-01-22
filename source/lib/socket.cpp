
#include "net/socket.hpp"

#include <errno.h>
#include <string.h>        // strerror
#include <sys/socket.h>    // socket
#include <sys/types.h>     // getsockopt
#include <unistd.h>        // close

#include <com/system_warn.hpp>

namespace miu::net {

socket::socket(int32_t raw)
    : _raw(raw) {}

socket::socket(int32_t family, int32_t type)
    : _raw(::socket(family, type, 0)) {}

socket::socket(socket&& another)
    : _raw(another._raw) {
    another._raw = -1;
}

socket&
socket::operator=(socket&& another) {
    std::swap(_raw, another._raw);
    return *this;
}

socket::~socket() {
    ::shutdown(_raw, SHUT_RDWR);
    ::close(_raw);
}

template<typename T>
T
getsockopt(int32_t sock, int32_t option) {
    T val;
    socklen_t len = sizeof(val);
    ::getsockopt(sock, SOL_SOCKET, option, (char*)&val, &len);
    return val;
}

bool
socket::reuseaddr() const {
    return getsockopt<int32_t>(_raw, SO_REUSEADDR) != 0;
}

bool
socket::acceptconn() const {
    return getsockopt<int32_t>(_raw, SO_ACCEPTCONN) != 0;
}

bool
socket::bind(address const& addr) {
    auto err = ::bind(_raw, addr.raw(), addr.len());
    if (err) {
        SYSTEM_WARN("socket bind", addr.str(), errno, strerror(errno));
    }
    return !err;
}

bool
socket::listen() {
    auto err = ::listen(_raw, 1);
    if (err) {
        SYSTEM_WARN("socket listen", errno, strerror(errno));
    }
    return !err;
}

}    // namespace miu::net
