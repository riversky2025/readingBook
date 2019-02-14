//
// Created by RS on 2019/1/24.
//

#ifndef CLION_FUNC21_H
#define CLION_FUNC21_H


#include <iostream>

class Func21 {
int & i;
public:
    Func21(int &i);
    void operator()(){
        for (int j = 0; j < 10000; ++j) {
            std::cout<<"dosome sthing"<<i<<std::endl;
        }
    }
};


#endif //CLION_FUNC21_H
