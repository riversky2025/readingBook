//
// Created by RS on 2019/3/8.
//

#ifndef CODE_DEMO611_H
#define CODE_DEMO611_H
#include <cstddef>
#include <iostream>
#include "../RunTest.h"
class Demo611 : public RunTest{
    void run() override {
        for (int i = 0; i < 10; ++i) {
            std::cout<<countCalls()<<std::endl;
        }
    }
    size_t  countCalls(){
        static size_t ctr=1;//只会调用一次
        return  ++ctr;
    }
};
#endif //CODE_DEMO611_H
