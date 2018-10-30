#include "observer.h"

A<ObserverStrat>::A(int ind) {
    index = ind;
}

void A<ObserverStrat>::update() {
    std::cout << "A::update() a" << index << " is updated from new state of B" << std::endl;
}

void Notifier::addSubscriber(A<ObserverStrat> *subscr) {
    subscribers.push_back(subscr);
}

void Notifier::notifySubscribers() {
    std::cout << "C::notify_subscribers() send notifications to all observers" << std::endl;
    for (A<ObserverStrat> *subscriber : subscribers) {
        subscriber->update();
    }
}

B<ObserverStrat>::B(C<ObserverStrat> *notifier_) {
    notifier = notifier_;
}

void B<ObserverStrat>::changeState() {
    std::cout << "B::changeState() has changed state of b" << std::endl;
    notifier->notifySubscribers();
}