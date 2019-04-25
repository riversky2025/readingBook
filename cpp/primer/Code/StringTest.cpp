#include <iostream>
#include "catch.hpp"
#include <string>
//
// Created by RS on 2019/3/15.
//
TEST_CASE("字符串测试"){
    using namespace std;
    SECTION("construct") {
        const char *cp = "hello World!!!";//以空字符串结束的数组
        char noNull[] = {'H', 'i'};
        string s1(cp);//拷贝cp中的字符知道遇到空字符,s1="Hello World!!!"
        REQUIRE("hello World!!!"==s1);
        string s2(noNull, 2);//从noNull拷贝两个字符;s2=="Hi"
        REQUIRE("Hi"==s2);
        string s3(noNull);//未定义:noNull不是以空字符串结束
        std::cout<<"s3:"<<s3<<std::endl;
        string s4{cp+6,5};//从cp[6]开始拷贝5个字符;s4=="World"
        REQUIRE(s4=="World");
        string s5(s1,6,5);//从s1[6]开始拷贝5个字符;s5="World"
        REQUIRE(s5=="World");
        string s6(s1,6);//从s1[6]开始拷贝,直至s1末尾;s6=="World!!!"
        REQUIRE(s6=="World!!!");
        string s7(s1,6,20);//正确,只拷贝s1到末尾;s7==World!!!
        REQUIRE(s7=="World!!!");
        try {
            string s8(s1,16);//抛出一个out_of_range异常
        }catch (std::exception & e){
            std::cout<<"exception:"<<e.what()<<std::endl;
        }
    }
    SECTION("substr"){
        string s("hello world");
        string s2=s.substr(0,5);
        REQUIRE("hello"==s2);
        string s3=s.substr(6);
        REQUIRE("world"==s3);
        string s4=s.substr(6,11);
        REQUIRE("world"==s4);
        try {
            string s5=s.substr(12);
        }catch (std::exception & e){
            std::cout<<"exception:"<<e.what()<<std::endl;
        }
    }
}

