cmake_minimum_required(VERSION 3.10)
project(clion)


set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp)
set(INC_DIR E:/libcommon/Boost/include/boost-1_63/ E:/libcommon/quickfix/include )
set(LINK_DIR E:/libcommon/Boost/lib E:/libcommon/quickfix/lib/64/md)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})

add_executable(clion main.cpp Abstruct.cpp Abstruct.h Demo211.cpp Demo211.h Func21.cpp Func21.h Demo24.cpp Demo24.h Demo27.cpp Demo27.h Demo28.cpp Demo28.h Demo281.cpp Demo281.h Demo31.cpp Demo31.h Demo33.cpp Demo33.h Demo34.cpp Demo34.h HierarchicalMutex.cpp HierarchicalMutex.h Demo39.cpp Demo39.h Demo311.cpp Demo311.h Demo313.cpp Demo313.h Demo43.cpp Demo43.h match/Market.cpp match/Market.h match/Order.h match/IDGenerator.h)