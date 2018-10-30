#include "mediator.h"

void B<MediatorStrat>::recv_req() {
    std::cout << "B::recv_req() object of class B get the request" << std::endl;
}

void Mediator::add_colleague(B<MediatorStrat> *b) {
    colleagues.push_back(b);
}
void Mediator::send_req_to_colleagues() {
    int index_of_B = arc4random_uniform((uint32_t) colleagues.size());
    std::cout << "C::send_req_to_colleagues() mediator resend request to b" << index_of_B << std::endl;
    colleagues[index_of_B]->recv_req();
}

A<MediatorStrat>::A(C<MediatorStrat> *c) {
    mediator = c;
}
void A<MediatorStrat>::send_to_mediator() {
    std::cout << "A::send_to_mediator() 'a' send request to mediator" << std::endl;
    mediator->send_req_to_colleagues();
}