#include <iostream>


// for typelist

class NullType {};

template<typename T = NullType, typename ... U>
struct TypeList {
    using Head = T;
    using Tail = TypeList<U ...>;
};

template<>
struct TypeList<> {
    using Head = NullType;
    using Tail = NullType;
};

using EmptyList = TypeList<>;


// for length

template<typename TList>
struct Length {
    enum { value = Length<typename TList::Tail>::value + 1 };
};

template<>
struct Length<NullType> {
    enum { value = 0 };
};

template<>
struct Length<EmptyList> {
    enum { value = 0 };
};


// for indexed access

template<typename TList, unsigned int index>
struct TypeAt;

template<typename TList>
struct TypeAt<TList, 0> {
    using result = typename TList::Head;
};

template<typename TList, unsigned int index>
struct TypeAt {
    using result = typename TypeAt<typename TList::Tail, index - 1>::result;
};


// for inserting by index

template<typename TList, unsigned int index, typename E>
struct InsertType;

template<typename Head, typename T, typename ... Tail>
struct InsertType<TypeList<Head, Tail ...>, 0, T> {
    using result = TypeList<T, Head, Tail ...>;
};

template<typename Head, typename T, unsigned int index, typename ... Tail>
struct InsertType<TypeList<Head, Tail ...>, index, T> {
    using result =typename InsertType<typename InsertType<TypeList<Tail ...>, index - 1, T>::result, 0, Head>::result;
};


// for erasing by index

template<typename TList, unsigned int index>
struct EraseType;

template<typename Head, typename ... Tail>
struct EraseType<TypeList<Head, Tail ...>, 0> {
    using result = TypeList<Tail ...>;
};

template<typename Head, unsigned int index, typename ... Tail>
struct EraseType<TypeList<Head, Tail ...>, index> {
    using result = typename InsertType<typename EraseType<TypeList<Tail ...>, index - 1>::result, 0, Head>::result;
};


// for getting first N types from list

template<typename TList, unsigned int N>
struct GetFirstN;

template<typename TList, unsigned int N>
struct GetFirstN {
    using result = typename std::conditional<(Length<TList>::value <= N),
                                             TList,
                                             typename InsertType<typename GetFirstN<TList, N - 1>::result,
                                                                 N - 1,
                                                                 typename TypeAt<TList,
                                                                                 N - 1>::result>::result>::type;

};

template<typename TList>
struct GetFirstN<TList, 0> {
    using result = EmptyList;
};


// for erasing first N types from list

template<typename TList, unsigned int N>
struct EraseFirstN;

template<typename TList, unsigned int N>
struct EraseFirstN {
    using result = typename std::conditional<(Length<TList>::value <= N),
                                             EmptyList,
                                             typename EraseFirstN<typename EraseType<TList, 0>::result,
                                                                  N - 1>::result>::type;
};

template<typename TList>
struct EraseFirstN<TList, 0> {
    using result = TList;
};


// for Linear Hierarchy

template<class T, class Base>
struct Unit : Base {
    T value;
};

template<typename TList, template<class, class> class Unit, class Root = NullType>
class GenLinearHierarchy;

template<typename Head, template<class, class> class Unit, class Root, typename ... Tail>
class GenLinearHierarchy<TypeList<Head, Tail ...>, Unit, Root> : public Unit<Head,
                                                                             GenLinearHierarchy<TypeList<Tail ...>,
                                                                                                Unit,
                                                                                                Root>> {
};

template<typename Tail, template<class, class> class Unit, class Root>
class GenLinearHierarchy<TypeList<Tail>, Unit, Root> : public Unit<Tail, Root> {};


// for Fibonacci numbers

template<int N>
struct Fibonacci {
    enum { value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value };
};

template<>
struct Fibonacci<0> {
    enum { value = 1 };
};

template<>
struct Fibonacci<1> {
    enum { value = 1 };
};


// for Fibonacci Hierarchy

template<typename TList, template<class, class> class Unit, unsigned int index>
class GenFibonacciHierarchyForNextBranch;

template<typename TList, template<class, class> class Unit, unsigned int index>
class GenFibonacciHierarchyForNextBranch : public GenLinearHierarchy<typename GetFirstN<TList,
                                                                                        Fibonacci<index>::value>::result,
                                                                     Unit>,
                                           public GenFibonacciHierarchyForNextBranch<typename EraseFirstN<TList,
                                                                                                          Fibonacci<
                                                                                                              index>::value>::result,
                                                                                     Unit,
                                                                                     index + Fibonacci<index>::value> {
};

template<template<class, class> class Unit, unsigned int index>
class GenFibonacciHierarchyForNextBranch<EmptyList, Unit, index> {};

template<typename TList, template<class, class> class Unit>
class GenFibonacciHierarchy;

template<typename TList, template<class, class> class Unit>
class GenFibonacciHierarchy : public GenFibonacciHierarchyForNextBranch<TList, Unit, 0> {};


// for testing

class T1 {};
class T2 {};
class T3 {};
class T4 {};
class T5 {};
class T6 {};
class T7 {};
class T8 {};

typedef TypeList<T1, T2, T3, T4, T5, T6, T7, T8> TList;

int main() {
    GenFibonacciHierarchy<TList, Unit> f;
    return 0;
}