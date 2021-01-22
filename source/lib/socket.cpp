
#include "net/socket.hpp"

#include <errno.h>
#include <fcntl.h>
#include <string.h>        // strerror
#include <sys/socket.h>    // socket
#include <sys/types.h>     // getsockopt
#include <unistd.h>        // close

#include <com/system_warn.hpp>
#include <log/log.hpp>

namespace miu::net {

// static int32_t
// send_stream(int32_t raw, const void* data, int32_t size) {
//    return ::send(raw, data, size, MSG_NOSIGNAL);
//}

// static int32_t send_dgram(socket const* sock, const void* buf, int32_t n) {
//    auto addr = sock->remote()->val();
//    auto addr_len = sock->remote()->len();
//    return ::sendto(sock->raw(), buf, n, MSG_NOSIGNAL, addr, addr_len);
//}

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

void
socket::set_reuseaddr(bool v) {
    int32_t val = v ? 1 : 0;
    ::setsockopt(_raw, SOL_SOCKET, SO_REUSEADDR, (const char*)&val, sizeof(val));
}

bool
socket::acceptconn() const {
    return getsockopt<int32_t>(_raw, SO_ACCEPTCONN) != 0;
}

bool
socket::nonblock() const {
    return (::fcntl(_raw, F_GETFL) & O_NONBLOCK) != 0;
}

bool
socket::bind(address const& addr) {
    auto err = ::bind(_raw, addr.raw(), addr.len());
    if (err) {
        log::error(+"socket bind", addr.str(), errno, (const char*)strerror(errno));
    }
    return !err;
}

bool
socket::listen() {
    auto err = ::listen(_raw, 1);
    if (err) {
        log::error(+"socket listen", errno, (const char*)strerror(errno));
    }
    return !err;
}

socket
socket::accept() {
    sockaddr_in addr {};
    uint32_t addrlen = sizeof(addr);
    auto cli = ::accept(_raw, (sockaddr*)&addr, &addrlen);
    if (cli < 0) {
        log::error(+"socket accept", errno, (const char*)strerror(errno));
    }

    return { cli };
}

bool
socket::connect(address const& addr) {
    if (::connect(_raw, addr.raw(), addr.len())) {
        log::error(+"socket connect", errno, (const char*)strerror(errno));
        return false;
    }

    return true;
}

bool
socket::send(const void* data, uint32_t size) {
    auto err = ::send(_raw, data, size, MSG_NOSIGNAL);
    if (err < 0) {
        log::error(+"socket send", errno, (const char*)strerror(errno));
    }
    return err > 0;
}

int32_t
socket::recv(void* buf, uint32_t len) {
    auto recv_len = ::recvfrom(_raw, buf, len, MSG_NOSIGNAL, nullptr, nullptr);
    if (recv_len < 0) {
        log::error(+"socket recv", errno, (const char*)strerror(errno));
    }
    return recv_len;
}

}    // namespace miu::net
