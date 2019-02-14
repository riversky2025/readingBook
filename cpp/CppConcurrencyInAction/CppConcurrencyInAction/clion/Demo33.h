//
// Created by RS on 2019/1/25.
//

#ifndef CLION_DEMO33_H
#define CLION_DEMO33_H


#include <deque>
#include "Abstruct.h"

template<typename T, typename Container=std::deque<T>>
class Demo33 : public Abstruct {
public:
    void run() override;

//    explicit Demo33(const Container &) {};
//
//    explicit Demo33(Container && = Container()) {};
//
//    template<class Alloc>
//    explicit Demo33(const Alloc &) {};
//
//    template<class Alloc>
//    Demo33(const Container &, const Alloc &) {};
//
//    template<class Alloc>
//    Demo33(Container &&, const Alloc &) {};
//
//    template<class Alloc>
//    Demo33(Demo33 &&, const Alloc &) {};
//
//    virtual  bool empty() const =0;
//
//    virtual size_t size() const=0;
//    virtual T &top()=0;
//    virtual T const &top() const=0;
//    virtual void push(T const &)=0;
//    virtual void push(T &&)=0;
//    virtual void pop()=0;
//
//    virtual void swap(Demo33 &&)=0;
};

template<typename T, typename Container>
void Demo33<T, Container>::run() {

}


#endif //CLION_DEMO33_H
