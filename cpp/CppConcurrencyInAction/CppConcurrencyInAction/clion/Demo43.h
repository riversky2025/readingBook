//
// Created by RS on 2019/2/12.
//

#ifndef CLION_DEMO43_H
#define CLION_DEMO43_H


#include <memory>
#include <mutex>
#include <queue>
#include "Abstruct.h"

template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() {

    }

    ThreadSafeQueue(const ThreadSafeQueue &other) {
        std::lock_guard<std::mutex> lk(mut);
        data_queue=other.data_queue;
    }

    ThreadSafeQueue &operator=(const ThreadSafeQueue &)= delete;//不允许简单的赋值
    void push(T newValue);

    bool tryPop(T &value);

    std::shared_ptr<T> tryPop();

    void waitAndPop(T &value);

    std::shared_ptr<T> waitAndPop();

    bool empty() const;

private:
    mutable std::mutex mut;//1 互斥量必须是可变的
    std::queue<T> data_queue;
    std::condition_variable data_cond;
};


class Demo43 : public Abstruct {
    void run() override;
};


#endif //CLION_DEMO43_H
