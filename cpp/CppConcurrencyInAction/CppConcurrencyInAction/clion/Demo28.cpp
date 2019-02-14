//
// Created by RS on 2019/1/24.
//

#include <iterator>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <cstdint>
//#include <stdint-gcc.h>
#include "Demo28.h"

void Demo28::run() {
    std::vector<int> a;
    for (int i = 0; i < 10000; ++i) {
        a.push_back(i);
    }
    auto itbegin = a.begin();
    auto itend = a.end();
    int result = parallel_accumulate<std::vector<int>::iterator, int>(itbegin, itend, 0);
    std::cout << result << std::endl;
//    int result = 0;
//    std::cout << std::accumulate(a.begin(), a.end(), result);
}

template<typename Iterator, typename T>
T Demo28::parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length = std::distance(first, last);
    if (!length) {
        return init;
    }
    uint64_t const minPerThread = 25;
    uint64_t const maxThread = (length + minPerThread - 1) / minPerThread;
    uint64_t const hardwareThread = std::thread::hardware_concurrency();
    uint64_t const numThread = std::min(maxThread, hardwareThread == 0 ? 2 : hardwareThread);
    uint64_t const blockSize = length / numThread;
    std::vector<T> results(numThread);
    std::vector<std::thread> threads(numThread);
    Iterator blockStart = first;
    for (int i = 0; i < (numThread - 1); ++i) {
        Iterator blockEnd = blockStart;
        std::advance(blockEnd, blockSize);//迭代器自增函数
        threads[i] = std::thread(accumulate_block<Iterator, T>(), blockStart, blockEnd, std::ref(results[i]));
        blockStart = blockEnd;
    }
    accumulate_block<Iterator, T>()(blockStart, last, results[numThread - 1]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    std::accumulate(results.begin(), results.end(), init);
    return init;
}
