//
// Created by RS on 2019/1/25.
//

#include <iostream>
#include <thread>
#include "Demo281.h"

void Demo281::run() {
    for (int i = 0; i < 5; ++i) {
        std::thread t([](){
            std::cout<<std::this_thread::get_id()<<std::endl;
        });
        t.join();
    }


}
