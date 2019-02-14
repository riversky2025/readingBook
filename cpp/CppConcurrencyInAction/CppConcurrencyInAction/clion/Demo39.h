//
// Created by RS on 2019/1/30.
//
#ifndef CLION_DEMO39_H
#define CLION_DEMO39_H
#include <mutex>
#include <iostream>
#include "Abstruct.h"
class BigObj{
public:
    BigObj(int x1,int y1):x(x1),y(y1){}
    int x=0;
    int y=0;
};
void swap3(BigObj &left,BigObj &right);
class Demo39 :public Abstruct{
public:
    BigObj sodata;
    std::mutex mutex;
public:
    Demo39(BigObj const& sd):sodata(sd){}
    friend void swap(Demo39 & lhs,Demo39& rhs);
    void run() override {
        BigObj obj1({2,3});
        BigObj obj2({4,5});
        Demo39 demo39(obj1);
        Demo39 demo391(obj2);
        std::cout<<demo39.sodata.x<<std::endl;
        swap(demo39,demo391);
        std::cout<<demo39.sodata.x<<std::endl;
    }
};
#endif //CLION_DEMO39_H
