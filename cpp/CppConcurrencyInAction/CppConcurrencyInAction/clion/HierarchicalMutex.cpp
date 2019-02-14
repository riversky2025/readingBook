//
// Created by RS on 2019/1/29.
//

#include "HierarchicalMutex.h"

thread_local uint64_t HierarchicalMutex::thisThreadHierarchyValue(ULONG_MAX);