//
// Created by RS on 2019/2/27.
//

#ifndef CODE_DEMO342_H
#define CODE_DEMO342_H


#include "../RunTest.h"
#include <vector>
#include <iostream>

class Demo342 : public RunTest {
public:
    void run() override {
        std::vector<int> a{1,2,3,4,5,6,7,8};
        auto va=search(a,7);
        std::cout<<"ans:"<<a[va]<<std::endl;
        std::cout<<__cplusplus<<std::endl;
    }
    template<typename T>
    int search(std::vector<T> &v, const T &value) {
        auto beg = v.begin(), end = v.end(), mid = v.begin() + (v.end()-v.begin()) / 2;
        while (mid != end && *mid != value) {
            if(*mid>value){
                end=mid-1;
            }else{
                beg=mid;
            }
            mid=beg+(end-beg)/2;
        }
        return mid-v.begin();
    }
};


#endif //CODE_DEMO342_H
