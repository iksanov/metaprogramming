#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include "template_classes.h"

template <>
class A<ObserverStrat> {
  private:
    int index = 0;
  public:
    explicit A(int ind);
    void update();
};

class Notifier {
  private:
    std::vector<A<ObserverStrat>*> subscribers;
  public:
    void addSubscriber(A<ObserverStrat> *subscr);
    void notifySubscribers();
};

template <>
class C<ObserverStrat>: public Notifier {};

template <>
class B<ObserverStrat> {
  private:
    C<ObserverStrat> *notifier{};
  public:
    explicit B(C<ObserverStrat> *notifier_);
    virtual void changeState();
};


//
//int main() {
//    A<ObserverStrat> *a1 = new A<ObserverStrat>(1);
//    A<ObserverStrat> *a2 = new A<ObserverStrat>(2);
//    C<ObserverStrat> *c = new C<ObserverStrat>();
//    B<ObserverStrat> *b = new B<ObserverStrat>(c);
//
//    c->addSubscriber(a1);
//    c->addSubscriber(a2);
//    b->changeState();
//
//    delete b;
//    delete c;
//    delete a1;
//    delete a2;
//
//    return 0;
//}