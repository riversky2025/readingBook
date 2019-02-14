//
// Created by RS on 2019/2/12.
//

#include <iostream>
#include "Demo43.h"



template<typename T>
void ThreadSafeQueue<T>::waitAndPop(T &value) {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this] { return !data_queue.empty(); });
    value = data_queue.front();
    data_queue.pop();
}

template<typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::waitAndPop() {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk,[this]{return ! data_queue.empty();});
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return  res;
}

template<typename T>
bool ThreadSafeQueue<T>::tryPop(T &value) {
    std::lock_guard<std::mutex> lk(mut);
    if(data_queue.empty())
        return false;
    value=data_queue.front();
    data_queue.pop();
    return true;
}

template<typename T>
std::shared_ptr<T> ThreadSafeQueue<T>::tryPop() {
    std::lock_guard<std::mutex> lk(mut);
    if(data_queue.empty()){
        return std::shared_ptr<T> ();
    }
    std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
}

template<typename T>
bool ThreadSafeQueue<T>::empty() const {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
}

template<typename T>
void ThreadSafeQueue<T>::push(T newValue) {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(newValue);
    data_cond.notify_one();
}

void Demo43::run() {
    ThreadSafeQueue<int> threadSafeQueue;
    threadSafeQueue.push(3);
    int a=0;
    threadSafeQueue.tryPop(a);
    std::cout<<a<<std::endl;
}
