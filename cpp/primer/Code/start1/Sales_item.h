//
// Created by RS on 2019/2/21.
//

#ifndef CODE_SALES_ITEM_H
#define CODE_SALES_ITEM_H
#include <iostream>
#include <string>
class Sales_item {
    friend std::istream &operator>>(std::istream &, Sales_item &);
    friend std::ostream &operator<<(std::ostream &, const Sales_item &);
    friend bool operator<(const Sales_item &, const Sales_item &);
    friend bool operator==(const Sales_item &, const Sales_item &);
    friend  Sales_item  operator+(const Sales_item& lhs, const Sales_item& rhs);
public:
    Sales_item() : units_sold(0), revenue(0.0) {}
    Sales_item(const std::string &book):bookNo(book),units_sold(0),revenue(0.0){}
    Sales_item(std::istream &is){
        is>>*this;
    }
    Sales_item& operator +=(const Sales_item& rhs){
        units_sold+=rhs.units_sold;
        revenue+=rhs.revenue;
        return * this;
    }
    std::string isbn()const{
        return bookNo;
    }
    double avg_price()const {
        if(units_sold)
            return  revenue/units_sold;
        else
            return 0;
    }
    void setBookNo(const std::string &bookNo);
    void setUnits_sold(unsigned int units_sold);
    void setRevenue(double revenue);
private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
#endif //CODE_SALES_ITEM_H
