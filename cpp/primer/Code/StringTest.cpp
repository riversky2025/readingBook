#include <iostream>
#include "catch.hpp"
#include <string>
//
// Created by RS on 2019/3/15.
//
TEST_CASE("�ַ�������"){
    using namespace std;
    SECTION("construct") {
        const char *cp = "hello World!!!";//�Կ��ַ�������������
        char noNull[] = {'H', 'i'};
        string s1(cp);//����cp�е��ַ�֪���������ַ�,s1="Hello World!!!"
        REQUIRE("hello World!!!"==s1);
        string s2(noNull, 2);//��noNull���������ַ�;s2=="Hi"
        REQUIRE("Hi"==s2);
        string s3(noNull);//δ����:noNull�����Կ��ַ�������
        std::cout<<"s3:"<<s3<<std::endl;
        string s4{cp+6,5};//��cp[6]��ʼ����5���ַ�;s4=="World"
        REQUIRE(s4=="World");
        string s5(s1,6,5);//��s1[6]��ʼ����5���ַ�;s5="World"
        REQUIRE(s5=="World");
        string s6(s1,6);//��s1[6]��ʼ����,ֱ��s1ĩβ;s6=="World!!!"
        REQUIRE(s6=="World!!!");
        string s7(s1,6,20);//��ȷ,ֻ����s1��ĩβ;s7==World!!!
        REQUIRE(s7=="World!!!");
        try {
            string s8(s1,16);//�׳�һ��out_of_range�쳣
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

