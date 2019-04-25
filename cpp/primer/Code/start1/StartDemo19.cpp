//
// Created by RS on 2019/2/20.
//

#include <iostream>
#include "StartDemo19.h"
#include "StartDemo1.h"
#include "Sales_item.h"

void demo19() {
    int i = 50;
    int result = 0;
    while (i < 101) {
        result += i++;
    }
    std::cout << "50-100 sum:" << result << std::endl;
}

void demo110(int i) {
    while (i) {
        std::cout << i-- << std::endl;
    }
}

void demo11() {
    std::cout << "please input two num for print:" << std::endl;
    int a, b;
    std::cin >> a >> b;
    int min = a < b ? a : b;
    while (a > b) {
        if (b != min) {
            std::cout << b << ",";
        }
        b++;
    }
    std::cout << std::endl;
    while (a < b) {
        if (a != min) {
            std::cout << a << ",";
        }
        a++;
    }
    std::cout << std::endl;
}

void demo143() {
    int sum = 0, value = 0;
    while (std::cin >> value) {
        sum += value;
    }
    std::cout << "sum:" << sum << std::endl;
}

void demo144() {
    int cur = 0, val = 0;

    if (std::cin >> cur) {
        int cnt = 1;
        while (std::cin >> val) {
            if (val == cur) {
                cnt++;
            } else {
                std::cout << cur << ":" << cnt << std::endl;
                cur = val;
                cnt = 1;
            }
        }
        std::cout << cur << ":" << val << std::endl;
    }
}

void demo152() {
    Sales_item item1, item2;
    std::cin >> item1 >> item2;
    if (item1.isbn() == item2.isbn()) {
        std::cout << item1 + item2 << std::endl;
    } else {
        std::cerr << "Data must refer to same ISBN" << std::endl;
    }
}
void demo16(){
    Sales_item total;//保存下一条记录
    if(std::cin>>total){
        Sales_item trans;//保存和变量
        while (std::cin>>trans){
            if(total.isbn()==trans.isbn())
                total+=trans;
            else{
                std::cout<<total<<std::endl;
                total=trans;
            }
        }
        std::cout<<total<<std::endl;//打印最后一本书的结果
    }else{
        std::cerr<<"No data?!"<<std::endl;
    }
}

void StartDemo19::run() {
 int m1=12,d1=7,m2=012,d2=07;
 std::cout<<m1<<" "<<d1<<std::endl;
 std::cout<<m2<<" "<<d2<<std::endl;

}
