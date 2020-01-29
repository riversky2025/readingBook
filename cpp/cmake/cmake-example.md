# 1. CMake使用简介
CMake是一个跨平台的开源元构建系统，可以构建，测试和打包软件。它可以用于支持多个本机构建环境，包括make，Apple的xcode和Microsoft Visual Studio。  
该存储库包含一些现代CMake配置示例，我在探索其在各种项目中的用法时已经选择了它们。这些示例以类似教程的格式进行布局。第一个示例非常基础，并且在先前示例的基础上逐渐增加了复杂性，以显示更复杂的用例。  
# 2. 基础
[源码](https://github.com/Liwins/cmake-examples)  
## 2.1. 简介
主要包含11个使用场景,以及各种场景下的cmakelist的解释  
基本环境  
```
The easiest way to install the above on Ubuntu is as follows

$ sudo apt-get install build-essential
$ sudo apt-get install cmake
Some specific examples may require other tools including:

boost

$ sudo apt-get install libboost-all-dev
protobuf

$ sudo apt-get install libprotobuf-dev
$ sudo apt-get install protobuf-compiler
cppcheck

$ sudo apt-get install cppcheck
clang

$ sudo apt-get install clang-3.6
ninja

$ sudo apt-get install ninja-build
conan

$ sudo apt-get install python3 python3-pip
$ sudo pip3 install conan
```
## 2.2. 简单使用
简单项目  
### 2.2.1. 项目结构 
```
A-hello-cmake$ tree
.
├── CMakeLists.txt
├── main.cpp
```
### 2.2.2. CMakefile命令
```
//cmake最小支持版本
cmake_minimum_required(VERSION 3.5)
//项目名称-多项目中用于区分
project(hello_cmake)
//创建一个可执行文件,从main.cpp中执行文件,第一个参数是要生成的可执行文件名称,第二个是要编译的源文件列表
add_executable(hello_cmake main.cpp)
//或者使用${PROJECT_NAME} 替代
//add_executable(${PROJECT_NAME} main.cpp)
```

### 2.2.3. main.cpp  
```
#include <iostream>
int main(int argc, char* argv[]) {
	std::cout << "hello cmake" << std::endl;
	return 0;
}
```
### 2.2.4. ubuntu中进行如下操作  
```
//进入源文件目录
cd /src
//创建构建目录
mkdir build 
//执行cmake 
cmake ..
//执行make
make 
//这时候就可以执行了
./hello_cmake 
```
## 2.3. 头文件
### 2.3.1. 简介
主要是通过将头文件导入,以及源文件目录设置搞定就可以了
```
root@DESKTOP-MP32LRE:~/cmake-examples/01-basic/B-hello-headers# tree .
.
├── CMakeLists.txt
├── README.adoc
├── include
│   └── Hello.h
└── src
    ├── Hello.cpp
    └── main.cpp
```
### 2.3.2. CMakeList.txt
```
//最小版本
cmake_minimum_required(VERSION 3.5)
//项目名称
project(hello_headers)
//源文件变量-编译的 注意这里也可以使用 src/*.cpp 通配符替换
set(SOURCE src/Hello.cpp src/main.cpp)
//可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})
//include目录添加,为了是编译器将该头文件编译到target中  PRIVATE指定了包含范围
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
```
>> CMAKE中的变量

| 变量                     | 信息                                        |
| :----------------------- | :------------------------------------------ |
| CMAKE_SOURCE_DIR         | 源文件目录                                  |
| CMAKE_URRENT_SOURCE      | 当前源目录(如果是子项目,或者目录的话)       |
| PROJECT_SOURCE_DIR       | 当前cmake项目的源目录                       |
| CMAKE_BINARY_DIR         | 根二进制/构建目录.这是您运行cmake命令的目录 |
| CMAKE_CURRENT_BINARY_DIR | 您当前所在的构建目录                        |
| PROJECT_BINARY_DIR       | 当前项目的构建目录                          |
### 2.3.3. 源文件
Hello.h
```
#pragma once
class Hello {
public:
	void print();
};
```
hello.cpp
```
#include "Hello.h"
#include <iostream>
void Hello::print()
{
    std::cout<<"header hello"<<std::endl;
}
```
main.cpp
```
#include "Hello.h"
int main(int argc, char** argv) {
	Hello hi;
	hi.print();
	return 0;
}
```
## 2.4. 测试
```
mkdir build 
cd build
cmake ..
make .
运行
```
## 2.5. 静态库
### 2.5.1. 简介
项目中根据代码生成静态库,并且运行中使用该生成的静态库进行链接  
```
.
├── CMakeLists.txt
├── README.adoc
├── include
│   └── static
│       └── Hello.h
└── src
    ├── Hello.cpp
    └── main.cpp
```
其中Hello.h Hello.cpp是用于生成静态库的
main.cpp是用于生成执行文件的
### 2.5.2. CMakeLists.txt  
```
cmake_minimum_required(VERSION 3.5)
project(hello_library)
#生成一个静态库 将静态库需要编译的都加进来
add_library(${PROJECT_NAME} STATIC src/Hello.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

## 生成一个执行可运行项目 只使用main.cpp 编译生成可以运行的cpp
add_executable(hello_binary src/main.cpp)
# 链接
target_link_libraries(hello_binary PRIVATE ${PROJECT_NAME})
```
>> 切记库的名字不要和exe生成的一样  

**add_library()** 
用于从某些源文件创建一个库.  

linux环境下libhello_library.a
winddow下为hello_library.lib  
**target_include_directories**      

这里我们将范围写成PUBLIC   
作用是:
1. 编译库时包含该目录
2. 编译连接库的任何其他目标是也包含该目录  

范围的含义  
* PRIVATE-目录只添加到该目标的库
*  INTERFACE-目录添加到连接该库的目标
*  PUBLIC-PRIVATE+INTERFACE 
>> 最佳实践,一般用于PUBLIC时,都会添加子目录(命名空间),用于避免与其他库的头文件冲突
### 2.5.3. 项目文件  

## 2.6. 动态库
### 2.6.1. 简介  
```
./
├── CMakeLists.txt
├── README.adoc
├── include
│   └── shared
│       └── Hello.h
└── src
    ├── Hello.cpp
    └── main.cpp
```
该方案只能在linux下测试成功
### 2.6.2. CMakeLists.txt
```
cmake_minimum_required(VERSION 3.5)

project(hello_library)

############################################################
# Create a library
############################################################

#Generate the shared library from the library sources
add_library(hello_library SHARED 
    src/Hello.cpp
)
add_library(hello::library ALIAS hello_library)

target_include_directories(hello_library
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

############################################################
# Create an executable
############################################################

# Add an executable with the above sources
add_executable(hello_binary
    src/main.cpp
)

# link the new hello_library target with the hello_binary target
target_link_libraries( hello_binary
    PRIVATE 
        hello::library
)
```

## 2.7. 安装-> 生成make install 目标 
使用感觉就是将自己生成的文件,通过make install 分别复制到指定的文件夹
```
cmake_minimum_required(VERSION 3.5)

project(cmake_examples_install)

############################################################
# Create a library
############################################################

#Generate the shared library from the library sources
add_library(cmake_examples_inst SHARED
    src/Hello.cpp
)

target_include_directories(cmake_examples_inst
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

############################################################
# Create an executable
############################################################

# Add an executable with the above sources
add_executable(cmake_examples_inst_bin
    src/main.cpp
)

# link the new hello_library target with the hello_binary target
target_link_libraries( cmake_examples_inst_bin
    PRIVATE 
        cmake_examples_inst
)

############################################################
# Install
############################################################

# Binaries
install (TARGETS cmake_examples_inst_bin
    DESTINATION bin)

# Library
# Note: may not work on windows
install (TARGETS cmake_examples_inst
    LIBRARY DESTINATION lib)

# Header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ 
    DESTINATION include)

# Config
install (FILES cmake-examples.conf
    DESTINATION etc)
```  

### 2.7.1. 平台差异  
对于windows平台的库  
可能需要修改为以下代码  
```
install (TARGETS cmake_examples_inst
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
```
### 2.7.2. 修改目录  
1. 一般指定的文件
如果不想安装到/usr/local,通过以下切换.  
```
cmake.. -DCMAKE_INSTALL_PREFIX= /install/location
```
2. make install DESTDIR=/tmp/stage
### 2.7.3. 卸载
```
sudo xargs rm < install_manifest.txt
```
## 2.8. 编译类型
在编译前可以使用使用cmake中的判断进行编译标志的设置  
```
cmake_minimum_required(VERSION 3.13)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message("Setting build type to 'RelWithDebInfo' as none was specified.")
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")

endif ()

project(build_type)


set(CMAKE_CXX_STANDARD 11)

add_executable(build_type main.cpp)
```

下面分别使用三种方式进行编译  
```
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake ..
```
其大小分别是 
```
root@DESKTOP-MP32LRE:~/cmake-examples/01-basic/F-build-type/build# ll
total 116
drwxr-xr-x 3 root root  4096 Dec 13 14:46 ./
drwxr-xr-x 3 root root  4096 Dec 13 14:42 ../
-rw-r--r-- 1 root root 12896 Dec 13 14:46 CMakeCache.txt
drwxr-xr-x 5 root root  4096 Dec 13 14:46 CMakeFiles/
-rw-r--r-- 1 root root  5107 Dec 13 14:46 Makefile
-rwxr-xr-x 1 root root 28992 Dec 13 14:46 cmake_examples_build_type*
-rwxr-xr-x 1 root root  8768 Dec 13 14:44 cmake_examples_build_type-back*
-rwxr-xr-x 1 root root 32056 Dec 13 14:44 cmake_examples_build_type-demo*
-rw-r--r-- 1 root root  1541 Dec 13 14:46 cmake_install.cmake
root@DESKTOP-MP32LRE:~/cmake-examples/01-basic/F-build-type/build# ./cmake_examples_build_type
Hello Build Type!
root@DESKTOP-MP32LRE:~/cmake-examples/01-basic/F-build-type/build# ./cmake_examples_build_type-demo
Hello Build Type!
root@DESKTOP-MP32LRE:~/cmake-examples/01-basic/F-build-type/build# ./cmake_examples_build_type-back
Hello Build Type!
root@DESKTOP-MP32LRE:~/cmake-examples/01-basic/F-build-type/build#
```
## 2.9. 编译标志  
编译标志位的使用主要有3种使用场景  
1. target_compile_definitions()
2. 使用CMAKE_C_FLAGS和CMAKE_CXX_FLAGS变量。--全局带缓存  
3. cmake .. 指令传递  

前两种使用方法   
项目源码:
```
#include <iostream>
int main() {
#ifdef EX2
    std::cout<<"Ex2 编译选项"<<std::endl;
#endif
#ifdef EX3
    std::cout<<"Ex3 编译选项"<<std::endl;
#endif

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```
```
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX3" CACHE STRING "SET C++ Compiler Flags" FORCE )

project(comple_flags)

set(CMAKE_CXX_STANDARD 11)

add_executable(comple_flags main.cpp)

target_compile_definitions(comple_flags PRIVATE EX2)
```
>>  推荐使用第一种,第三种一般是为开源库或者三方库提供,编译标志.
## 2.10. 三方库
### 2.10.1. 简介
这里说的三方库是安装到系统中的三方动态,或静态库  
```
make_minimum_required(VERSION 3.5)

# Set the project name
project (third_party_include)


#需要安装boost 1.46.1以上的版本,并且需要有filessystem system 模块
find_package(Boost 1.46.1 REQUIRED COMPONENTS filesystem system)

# check if boost was found
if(Boost_FOUND)
    message ("boost found")
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()

# Add an executable
add_executable(third_party_include main.cpp)

# link against the boost libraries
target_link_libraries( third_party_include
    PRIVATE
        Boost::filesystem
)
```
## 2.11. 使用clang编译 
环境测试  
```
ROOT_DIR=`pwd`
dir="01-basic/I-compiling-with-clang"

if [ -d "$ROOT_DIR/$dir/build.clang" ]; then
    echo "deleting $dir/build.clang"
    rm -r $dir/build.clang
fi
```
运行编译
```
#!/bin/bash
# Ubuntu supports multiple versions of clang to be installed at the same time.
# The tests need to determin the clang binary before calling cmake
clang_bin=`which clang`
clang_xx_bin=`which clang++`

if [ -z $clang_bin ]; then
    clang_ver=`dpkg --get-selections | grep clang | grep -v -m1 libclang | cut -f1 | cut -d '-' -f2`
    clang_bin="clang-$clang_ver"
    clang_xx_bin="clang++-$clang_ver"
fi

echo "Will use clang [$clang_bin] and clang++ [$clang_xx_bin]"


mkdir -p build.clang && cd build.clang && \
    cmake .. -DCMAKE_C_COMPILER=$clang_bin -DCMAKE_CXX_COMPILER=$clang_xx_bin && make
```
## 2.12. 使用ninja编译
环境测试  
```
#!/bin/bash

ROOT_DIR=`pwd`
dir="01-basic/J-building-with-ninja"

if [ -d "$ROOT_DIR/$dir/build.ninja" ]; then
    echo "deleting $dir/build.ninja"
    rm -r $dir/build.ninja
fi
```
运行测试
```
#!/bin/bash
# Travis-ci cmake version doesn't support ninja, so first check if it's supported
ninja_supported=`cmake --help | grep Ninja`

if [ -z $ninja_supported ]; then
    echo "Ninja not supported"
    exit
fi

mkdir -p build.ninja && cd build.ninja && \
    cmake .. -G Ninja && ninja
```
## 2.13. 连接boost目标  
```
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (imported_targets)


# find a boost install with the libraries filesystem and system
find_package(Boost 1.46.1 REQUIRED COMPONENTS filesystem system)

# check if boost was found
if(Boost_FOUND)
    message ("boost found")
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()

# Add an executable
add_executable(imported_targets main.cpp)

# link against the boost libraries
target_link_libraries( imported_targets
    PRIVATE
        Boost::filesystem
)
```
## 2.14. 设置c++标准库的各种方法  
```
set(CMAKE_CXX_STANDARD 11)
```
# 3. 子项目
大项目通常是由几个小项目构成  
## 基本使用  

# 4. 代码生成
# 5. 静态分析
# 6. 单元测试
# 7. 安装程序
# 8. 包管理
# 9. dockerfile

