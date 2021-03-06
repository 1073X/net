#pragma once

#include <cstdint>
#include <time/delta.hpp>

#include "address.hpp"

namespace miu::net {

class socket {
  public:
    socket(int32_t = -1);
    socket(int32_t family, int32_t type);
    socket(socket&&);
    socket& operator=(socket&&);
    ~socket();

    auto operator!() const { return _raw < 0; }
    operator bool() const { return !operator!(); }

    auto raw() const { return _raw; }
    int32_t type() const;
    bool acceptconn() const;

    bool reuseaddr() const;
    void set_reuseaddr(bool);

    time::delta timeout() const;
    void set_timeout(time::delta);

    bool nodelay() const;
    void set_nodelay(bool);

    int32_t sndbuf() const;
    void set_sndbuf(int32_t);

    int32_t rcvbuf() const;
    void set_rcvbuf(int32_t);

    bool nonblock() const;
    void set_nonblock(bool);

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
