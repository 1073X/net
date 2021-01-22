#pragma once

#include <com/microseconds.hpp>
#include <cstdint>

#include "address.hpp"

namespace miu::net {

class socket {
  public:
    socket(int32_t = -1);
    socket(socket&&);
    socket& operator=(socket&&);
    socket(int32_t family, int32_t type);
    ~socket();

    auto operator!() const { return _raw < 0; }
    operator bool() const { return !operator!(); }

    auto raw() const { return _raw; }
    int32_t type() const;

    bool reuseaddr() const;
    void set_reuseaddr(bool);

    com::microseconds timeout() const;
    void set_timeout(com::microseconds);

    bool acceptconn() const;
    bool nonblock() const;

    bool bind(address const&);
    bool listen();
    socket accept();
    bool connect(address const&);

    int32_t send(const void* data, uint32_t size);
    int32_t recv(void* buf, uint32_t len);

  private:
    int32_t _raw { -1 };
};

}    // namespace miu::net
