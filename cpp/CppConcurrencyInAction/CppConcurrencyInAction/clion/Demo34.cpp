////
//// Created by RS on 2019/1/25.
////
//
//#include "Demo34.h"
//
//const char *empty_stack::what() const {
//    return "empty stack!";
//}
//template<typename T>
//Demo34<T>::Demo34(const Demo34 &other) {
//    std::lock_guard<std::mutex> lock(other.m);
//    data = other.data;//在构造函数中执行拷贝
//}
//
//template<typename T>
//void Demo34<T>::push(T newValue) {
//    std::lock_guard<std::mutex> lock(m);
//    data.push(newValue);
//}
///**
// * 通过弹出值的指针方式避免条件竞争
// * @tparam T
// * @return
// */
//template<typename T>
//std::shared_ptr<T> Demo34<T>::pop() {
//    std::lock_guard<std::mutex> lock(m);
//    if(data.empty()) throw empty_stack();
//    std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
//    data.pop();
//    return res;
//}
///**
// * 通过传入一个引用的方式避免竞争
// * @tparam T
// * @param value
// */
//template<typename T>
//void Demo34<T>::pop(T &value) {
//    std::lock_guard<std::mutex> lock(m);
//    if(data.empty()) throw empty_stack();
//    value=data.top();
//    data.pop();
//}
//
//template<typename T>
//bool Demo34<T>::empty() const {
//    std::lock_guard<std::mutex> lock(m);
//    return data.empty();
//}
