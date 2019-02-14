//
// Created by RS on 2019/1/31.
//

#include <memory>
#include <mutex>
#include "Demo311.h"
class SomeResource{
public:
    void dosomething(){}
    void reset(){}
};
void Demo311::run() {
    std::shared_ptr<SomeResource> resource_ptr;
    std::mutex resource_mutex;
//    void foo() {
//        std::unique_lock<std::mutex> lk(resource_mutex);//所有县城在此进行序列化
//        if(!resource_ptr){
//            resource_ptr.reset(new SomeResource);
//        }
//        lk.unlock();
//        resource_ptr->dosomething();
//    }
//    void undefined_behaiour_with_doble_checked_locking(){
//        if(!resource_ptr){//第一次校验
//            std::lock_guard<std::mutex> lk(resource_mutex);
//            if(!resource_ptr){//第二次校验
//                resource_ptr->reset();
//            }
//        }
//        resource_ptr->dosomething();
//    }
    std::shared_ptr<SomeResource> reso;

}
