//
// Created by RS on 2019/2/20.
//

#include <iostream>
#include "StartDemo1.h"
#include <string>
void StartDemo1::run() {
    std::string value,value2,value3 = "";
    std::cin >> value>>value2>>value3;
    std::cout<<"cout:"<<value<<std::endl;
    std::clog<<"clog:"<<value2<<std::endl;
    std::cerr<<"cerr:"<<value3<<std::endl;
}
