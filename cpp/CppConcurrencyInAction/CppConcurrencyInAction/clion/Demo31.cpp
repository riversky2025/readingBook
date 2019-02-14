//
// Created by RS on 2019/1/25.
//

#include <algorithm>
#include <iostream>
#include "Demo31.h"

void Demo31::run() {
    addToList(1);
    addToList(2);
    addToList(3);
    addToList(4);
    addToList(25);
    std::cout<<listContains(25)<<std::endl;
    std::cout<<listContains(21)<<std::endl;
}

bool Demo31::listContains(int valuetofind) {
    std::lock_guard<std::mutex> guard(someMutex);
    return std::find(someList.begin(), someList.end(), valuetofind) != someList.end();
}

void Demo31::addToList(int newValue) {
    std::lock_guard<std::mutex> lock(someMutex);
    std::cout<<"push:"<<newValue<<std::endl;
    someList.push_back(newValue);
}
