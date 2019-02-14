//
// Created by RS on 2019/1/24.
//

#include <iostream>
#include <thread>
#include "Demo24.h"

void Demo24::run() {
    char buff[1024];
    sprintf(buff,"%i",9);
    int c=3;
    std::thread t([this,c,buff](){
        std::cout<<c<<buff<<std::endl;
    });
    t.detach();
}

void Demo24::f(int a, std::string & demo) {
    std::cout<<a<<demo<<std::endl;
}



