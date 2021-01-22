#pragma once

namespace miu::net {

template<typename T>
auto
getsockopt(int32_t sock, int32_t option) {
    T val;
    socklen_t len = sizeof(val);
    ::getsockopt(sock, SOL_SOCKET, option, (char*)&val, &len);
    return val;
}

template<typename T>
auto
setsockopt(int32_t sock, int32_t option, T const& val) {
    return ::setsockopt(sock, SOL_SOCKET, option, (char*)&val, sizeof(T));
}

}    // namespace miu::net
