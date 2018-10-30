#include "mediator.h"
#include "observer.h"
#include "proxy.h"

void proxy_test() {
    std::cout << "PROXY" << std::endl << std::endl;

    IB_ProxyStrat *c = new C<ProxyStrat>();
    A<ProxyStrat> *a = new A<ProxyStrat>();
    a->send_to_proxy(c);
    delete a;
    delete c;

    std::cout  << std::endl << std::endl << std::endl;
}

void observer_test() {
    std::cout << "OBSEREVER" << std::endl << std::endl;

    A<ObserverStrat> *a1 = new A<ObserverStrat>(1);
    A<ObserverStrat> *a2 = new A<ObserverStrat>(2);
    C<ObserverStrat> *c = new C<ObserverStrat>();
    B<ObserverStrat> *b = new B<ObserverStrat>(c);

    c->addSubscriber(a1);
    c->addSubscriber(a2);
    b->changeState();

    delete b;
    delete c;
    delete a1;
    delete a2;

    std::cout  << std::endl << std::endl << std::endl;
}

void mediator_test() {
    std::cout << "MEDIATOR" << std::endl << std::endl;

    C<MediatorStrat> *c = new C<MediatorStrat>();
    B<MediatorStrat> *b1 = new B<MediatorStrat>();
    B<MediatorStrat> *b2 = new B<MediatorStrat>();
    B<MediatorStrat> *b3 = new B<MediatorStrat>();

    c->add_colleague(b1);
    c->add_colleague(b2);
    c->add_colleague(b3);

    A<MediatorStrat> *a = new A<MediatorStrat>(c);
    a->send_to_mediator();

    delete a;
    delete b3;
    delete b2;
    delete b1;
    delete c;

    std::cout  << std::endl << std::endl << std::endl;
}

int main() {
    proxy_test();
    observer_test();
    mediator_test();
    return 0;
}