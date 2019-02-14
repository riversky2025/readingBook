//
// Created by RS on 2019/1/29.
//

#ifndef CLION_HIERARCHICALMUTEX_H
#define CLION_HIERARCHICALMUTEX_H


#include <mutex>

class HierarchicalMutex {
     std::mutex internalMutex;
     uint64_t  const hierarchyValue;
     uint64_t previousHierarchyValue;
     static  thread_local uint64_t thisThreadHierarchyValue;
     void checkForHierarchyViolation(){
         if(thisThreadHierarchyValue<=hierarchyValue){
             throw  std::logic_error("mutex hierarchy violated");
         }
     }
     void updateHierarchyValue(){
         previousHierarchyValue=thisThreadHierarchyValue;
         thisThreadHierarchyValue=hierarchyValue;
     }

public:
    explicit HierarchicalMutex(uint64_t value):hierarchyValue(value),
                                               previousHierarchyValue(0){

     }
     void lock(){
         checkForHierarchyViolation();
         internalMutex.lock();
         updateHierarchyValue();
     }
     void unlock(){
         thisThreadHierarchyValue=previousHierarchyValue;
         internalMutex.unlock();
     }
     bool try_lock(){
         checkForHierarchyViolation();
         if(!internalMutex.try_lock()){
             return  false;
         }
         updateHierarchyValue();
         return true;
     }
};
#endif //CLION_HIERARCHICALMUTEX_H
