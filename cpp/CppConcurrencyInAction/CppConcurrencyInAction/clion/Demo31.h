//
// Created by RS on 2019/1/25.
//

#ifndef CLION_DEMO31_H
#define CLION_DEMO31_H


#include <mutex>
#include <list>
#include "Abstruct.h"

class Demo31 : public Abstruct{
public:
    void run() override;
    void addToList(int newValue);
    bool listContains(int valuetofind);
private:
    std::list<int> someList;
    std::mutex someMutex;
};


#endif //CLION_DEMO31_H
