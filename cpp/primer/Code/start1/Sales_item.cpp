//
// Created by RS on 2019/2/21.
//

#include "Sales_item.h"
std::ostream& operator<<(std::ostream& out, const Sales_item& s)
{
    out <<"<<" <<s.isbn() << " " << s.units_sold << " " << s.revenue << " " << s.avg_price();
    return out;
}
std::istream& operator>>(std::istream& in, Sales_item& s)
{
    double price;
    in >> s.bookNo >> s.units_sold >> price;
    // check that the inputs succeeded
    if (in)
        s.revenue = s.units_sold * price;
    else
        s = Sales_item();  // input failed: reset object to default state
    return in;
}
Sales_item operator+(const Sales_item& lhs, const Sales_item& rhs)
{
    Sales_item ret(lhs);  // copy (|lhs|) into a local object that we'll return
    ret += rhs;           // add in the contents of (|rhs|)
    return ret;           // return (|ret|) by value
}
bool operator==(const Sales_item &lhs, const Sales_item &rhs)
{
    // must be made a friend of Sales_item
    return lhs.units_sold == rhs.units_sold &&
           lhs.revenue == rhs.revenue &&
           lhs.isbn() == rhs.isbn();
}
bool operator<(const Sales_item &lhs, const Sales_item &rhs)
{
    // must be made a friend of Sales_item
    return  lhs.isbn() < rhs.isbn();
}
void Sales_item::setUnits_sold(unsigned int units_sold) {
    Sales_item::units_sold = units_sold;
}
void Sales_item::setRevenue(double revenue) {
    Sales_item::revenue = revenue;
}
bool operator!=(const Sales_item &lhs, const Sales_item &rhs)
{
    return !(lhs == rhs); // != defined in terms of operator==
}