#include "proxy.h"

void B<ProxyStrat>::recv_req() {
    std::cout << "B::recv_req() object of class B receive the request" << std::endl;
}

C<ProxyStrat>::C() {
    real_obj_ptr = new B<ProxyStrat>();
}

void C<ProxyStrat>::recv_req() {
    std::cout << "C::recv_req() proxy resend request to real object" << std::endl;
    real_obj_ptr->recv_req();
}

C<ProxyStrat>::~C() {
    delete real_obj_ptr;
}

void A<ProxyStrat>::send_to_proxy(IB_ProxyStrat *c) {
    std::cout << "A::send_to_proxy() 'a' send request to proxy of B" << std::endl;
    c->recv_req();
}