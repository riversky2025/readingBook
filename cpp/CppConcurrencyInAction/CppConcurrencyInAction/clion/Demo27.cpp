//
// Created by RS on 2019/1/24.
//

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include "Demo27.h"

void Demo27::run() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 20; ++i) {
        threads.push_back(std::thread(&Demo27::dowork,this,i));
        std::cout<<"线程数量"<<std::thread::hardware_concurrency()<<std::endl;
    }
    std::for_each(threads.begin(),threads.end(),std::mem_fn(&std::thread::join));
}

void Demo27::dowork(unsigned id) {
//    std::cout << id << std::endl;
}
