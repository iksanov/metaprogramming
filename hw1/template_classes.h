#pragma once

enum PatternStrat {
    ProxyStrat,
    MediatorStrat,
    ObserverStrat
};

template<PatternStrat T>
class A;

template<PatternStrat T>
class B;

template<PatternStrat T>
class C;