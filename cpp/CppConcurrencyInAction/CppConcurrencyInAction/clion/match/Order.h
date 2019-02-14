//
// Created by RS on 2019/2/13.
//

#ifndef CLION_ORDER_H
#define CLION_ORDER_H

#include <ostream>
#include <iomanip>
#include <string>
class Order{
    friend std::ostream  &operator<<(std::ostream&, const Order &);

public:

    enum Side{buy,sell};
    enum Type {market,limit};

    Order(const std::string &m_clientId, const std::string &m_symbol, const std::string &m_owner,
          const std::string &m_target, Side m_side, Type m_type, double m_price, long m_quantity) :
            m_clientId(m_clientId), m_symbol(m_symbol), m_owner(m_owner), m_target(m_target), m_side(m_side), m_type(m_type),
            m_price(m_price),m_quantity(m_quantity) {
        m_openQuantity=m_quantity;
        m_executedQuantity=0;
        m_avgExecutedPrice=0;
        m_lastExecutedPrice=0;
        m_lastExecutedQuantity=0;
    }

    const std::string &getM_clientId() const {
        return m_clientId;
    }

    const std::string &getM_symbol() const {
        return m_symbol;
    }

    const std::string &getM_owner() const {
        return m_owner;
    }

    const std::string &getM_target() const {
        return m_target;
    }

    Side getM_side() const {
        return m_side;
    }

    Type getM_type() const {
        return m_type;
    }

    double getM_price() const {
        return m_price;
    }

    long getM_quantity() const {
        return m_quantity;
    }

    long getM_openQuantity() const {
        return m_openQuantity;
    }

    long getM_executedQuantity() const {
        return m_executedQuantity;
    }

    double getM_avgExecutedPrice() const {
        return m_avgExecutedPrice;
    }

    double getM_lastExecutedPrice() const {
        return m_lastExecutedPrice;
    }

    long getM_lastExecutedQuantity() const {
        return m_lastExecutedQuantity;
    }
    bool isFilled()const {
        return m_quantity==m_executedQuantity;
    }
    bool isClosed()const {
        return m_openQuantity==0;
    }
    void execute(double price,long quantity){
        m_avgExecutedPrice=((quantity*price)+(m_avgExecutedPrice*m_executedQuantity)/(quantity+m_executedQuantity));
        m_openQuantity-=quantity;
        m_executedQuantity+=quantity;
        m_lastExecutedQuantity=price;
        m_lastExecutedQuantity=quantity;
    }
    void cancel(){
        m_openQuantity=0;
    }
private:
    std::string m_clientId;//客户ID
    std::string m_symbol;
    std::string m_owner;
    std::string m_target;
    Side m_side;//方向
    Type m_type;//单子类型
    double m_price;//价格
    long m_quantity;//数量

    long m_openQuantity;//当前挂单量
    long m_executedQuantity;//已成交数量
    double m_avgExecutedPrice;//平均成交价格
    double m_lastExecutedPrice;//最后成交价格
    long m_lastExecutedQuantity;//最后成交数量
};

inline std::ostream &operator<<(std::ostream & ostream, const Order& order) {
    return ostream<< "ID: " << std::setw( 10 ) << "," << order.getM_clientId()
                  << " OWNER: " << std::setw( 10 ) << "," << order.getM_owner()
                  << " PRICE: " << std::setw( 10 ) << "," << order.getM_price()
                  << " QUANTITY: " << std::setw( 10 ) << "," << order.getM_quantity();
}

#endif //CLION_ORDER_H
