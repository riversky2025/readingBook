////
//// Created by RS on 2019/1/25.
////
//
//#ifndef CLION_DEMO34_H
//#define CLION_DEMO34_H
//
//
//#include <bits/exception.h>
//#include <bits/shared_ptr.h>
//#include <stack>
//#include <mutex>
//#include "Abstruct.h"
//
//struct empty_stack : std::exception {
//    const char *what() const override;
//};
//
//template<typename T>
//class Demo34 : public Abstruct {
//public:
//    Demo34() : data(std::stack<T>()) {}
//
//    Demo34(const Demo34 &);
//
//    Demo34 &operator=(const Demo34 &)= delete;
//
//    void push(T newValue);
//
//    std::shared_ptr<T> pop();
//
//    void pop(T &value);
//
//    bool empty() const;
//
//    void run() override {
//
//    }
//
//private:
//    std::stack<T> data;
//    mutable std::mutex m;
//};
//
//
//
//#endif //CLION_DEMO34_H
