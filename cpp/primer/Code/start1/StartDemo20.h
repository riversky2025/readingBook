//
// Created by RS on 2019/2/25.
//

#ifndef CODE_STARTDEMO20_H
#define CODE_STARTDEMO20_H
#include <iostream>
#include "../RunTest.h"
class StartDemo20 : public RunTest{
private:
    int a,b;
    StartDemo20& fuben(){//返回引用是否正确
        return * this;
    }
    friend std::ostream & operator<<(std::ostream& os, const StartDemo20 & th);
public:
    StartDemo20(int a=0, int b=0) : a(a), b(b) {}
    void run() override {
       StartDemo20 de(1,2);
       StartDemo20 d23=de.fuben();
       d23.a=4;
       std::cout<<de<<std::endl;
       std::cout<<d23<<std::endl;
    }
};
std::ostream &operator<<(std::ostream& os, const StartDemo20 &th) {
    return os<<th.a<<":"<<th.b<<std::endl;
}
#endif //CODE_STARTDEMO20_H
