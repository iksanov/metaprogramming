#include <algorithm>
#include <iostream>
#include <vector>

enum PatternType {
  Proxy,
  Mediator,
  Observer
};

class IA;
class IB;

class INotifier {
 protected:
  std::vector<IA*> subscribers;
 public:
  virtual void add_subscriber(IA *subscr) = 0;
  virtual void notify_subscribers() = 0;
  virtual ~INotifier() = default;
};

class IMediator {
 protected:
  std::vector<IB*> colleagues;
 public:
  virtual void add_colleague(IB *b) = 0;
  virtual void send_req_to_colleagues() = 0;
  virtual ~IMediator() = default;
};

class IB {
 protected:
  INotifier *notifier{};

 public:
  virtual void change_state() = 0;
  virtual void recv_req() = 0;
  virtual ~IB() = default;
};

class B: public IB {
 public:
  B() = default;

  explicit B(INotifier *notifier_) {
    notifier = notifier_;
  }

  void change_state() override {
    std::cout << "B::change_state() has changed state of b" << std::endl;
    notifier->notify_subscribers();
  }

  void recv_req() override {
    std::cout << "B::recv_req() object of class B receive the request" << std::endl;
  }
};

class IA {
 protected:
  IMediator *mediator{};
  int index = 0;
 public:
  virtual void update() = 0;
  virtual void send_to_mediator() = 0;
  virtual void send_to_proxy(IB *c) = 0;
  virtual ~IA() = default;
};

class A: public IA {
 public:
  A() = default;

  explicit A(int ind) {
    index = ind;
  }

  explicit A(IMediator *c) {
    mediator = c;
  }

  void update() override {
    std::cout << "A::update() a" << index << " is updated from new state of B" << std::endl;
  }

  void send_to_mediator() override {
    std::cout << "A::send_to_mediator() 'a' send request to mediator" << std::endl;
    mediator->send_req_to_colleagues();
  }

  void send_to_proxy(IB *c) override {
    std::cout << "A::send_to_proxy() 'a' send request to proxy of B" << std::endl;
    c->recv_req();
  }
};

template <PatternType T>
class C;

template <>
class C<Proxy>: public IB {
 private:
  IB *real_obj_ptr;
 public:
  C() {
    real_obj_ptr = new B();
  }

  void recv_req() override {
    std::cout << "C::recv_req() proxy resend request to real object" << std::endl;
    real_obj_ptr->recv_req();
  }
  
  void change_state() override {}

  ~C() override {
    delete real_obj_ptr;
  }
};

template <>
class C<Mediator>: public IMediator {
 public:
  void add_colleague(IB *b) override {
    colleagues.push_back(b);
  }

  void send_req_to_colleagues() override {
    int index_of_B = arc4random_uniform((uint32_t)colleagues.size());
    std::cout << "C::send_req_to_colleagues() mediator resend request to b" << index_of_B << std::endl;
    colleagues[index_of_B]->recv_req();
  }
};

template <>
class C<Observer>: public INotifier {
 public:
  void add_subscriber(IA *subscr) override {
    subscribers.push_back(subscr);
  }

  void notify_subscribers() override {
    std::cout << "C::notify_subscribers() send notifications to all observers" << std::endl;
    for (IA *subscriber : subscribers) {
      subscriber->update();
    }
  }
};

void proxy_test() {
  std::cout << "PROXY" << std::endl << std::endl;

  IB *c = new C<Proxy>();
  IA *a = new A();
  a->send_to_proxy(c);
  delete a;
  delete c;

  std::cout  << std::endl << std::endl << std::endl;
}

void observer_test() {
  std::cout << "OBSEREVER" << std::endl << std::endl;

  IA *a1 = new A(1);
  IA *a2 = new A(2);
  INotifier *c = new C<Observer>();
  IB *b = new B(c);

  c->add_subscriber(a1);
  c->add_subscriber(a2);
  b->change_state();

  delete b;
  delete c;
  delete a1;
  delete a2;

  std::cout  << std::endl << std::endl << std::endl;
}

void mediator_test() {
  std::cout << "MEDIATOR" << std::endl << std::endl;

  IMediator *c = new C<Mediator>();
  IB *b1 = new B();
  IB *b2 = new B();
  IB *b3 = new B();

  c->add_colleague(b1);
  c->add_colleague(b2);
  c->add_colleague(b3);

  IA *a = new A(c);
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