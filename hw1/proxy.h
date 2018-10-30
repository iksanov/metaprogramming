#pragma once

#include <iostream>
#include "template_classes.h"

class IB_ProxyStrat {
  public:
    virtual ~IB_ProxyStrat() = default;
    virtual void recv_req() = 0;
};

template <>
class B<ProxyStrat>: public IB_ProxyStrat {
  public:
    void recv_req() override;
};

template <>
class C<ProxyStrat>: public IB_ProxyStrat {
  private:
    IB_ProxyStrat *real_obj_ptr;
  public:
    C();
    void recv_req() override;
    ~C() override;
};

template <>
class A<ProxyStrat> {
  public:
    void send_to_proxy(IB_ProxyStrat *c);
};