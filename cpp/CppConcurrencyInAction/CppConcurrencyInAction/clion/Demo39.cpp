//
// Created by RS on 2019/1/30.
//

#include "Demo39.h"

void swap3(BigObj &left,BigObj &right){
    BigObj tmp=left;
    left=right;
    right=tmp;
}

void swap(Demo39 &lhs, Demo39 &rhs) {
    if(&lhs==&rhs){
        return;
    }
    std::unique_lock<std::mutex> lock_a(lhs.mutex,std::defer_lock);
    std::unique_lock<std::mutex> lock_b(rhs.mutex,std::defer_lock);
    std::lock(lock_a,lock_b);//互斥量在这里上锁
    swap3(lhs.sodata,rhs.sodata);
}

