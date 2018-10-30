#pragma once

#include <vector>
#include <iostream>
#include "template_classes.h"

template<>
class B<MediatorStrat> {
  public:
    void recv_req();
};

class Mediator {
  private:
    std::vector<B<MediatorStrat> *> colleagues;
  public:
    void add_colleague(B<MediatorStrat> *b);
    void send_req_to_colleagues();
};

template<>
class C<MediatorStrat> : public Mediator {};

template<>
class A<MediatorStrat> {
  private:
    Mediator *mediator{};
  public:
    explicit A(C<MediatorStrat> *c);
    void send_to_mediator();
};

//int main() {
//    C<MediatorStrat> *c = new C<MediatorStrat>();
//    B<MediatorStrat> *b1 = new B<MediatorStrat>();
//    B<MediatorStrat> *b2 = new B<MediatorStrat>();
//    B<MediatorStrat> *b3 = new B<MediatorStrat>();
//
//    c->add_colleague(b1);
//    c->add_colleague(b2);
//    c->add_colleague(b3);
//
//    A<MediatorStrat> *a = new A<MediatorStrat>(c);
//    a->send_to_mediator();
//
//    delete a;
//    delete b3;
//    delete b2;
//    delete b1;
//    delete c;
//
//    return 0;
//}