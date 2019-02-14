//
// Created by RS on 2019/2/13.
//

#ifndef CLION_MARKET_H
#define CLION_MARKET_H


#include <map>
#include <queue>
#include "Order.h"
#include <string>
#include <functional>
/**
 * 行情类
 */
class Market {
public:
    /**
     * 添加订单
     * @param order
     * @return
     */
    bool insert(const Order &order);

    /**
     * 删除订单
     * @param order
     */
    void erase(const Order &order);

    /**
     * 查单
     * @param side 买卖方向
     * @param id
     * @return
     */
    Order &find(Order::Side side, std::string id);

/**
 * 撮合或者更新到买卖盘
 * @return
 */
    bool match(std::queue<Order> &);

    /**
     * 打印
     */
    void display() const;

private:
    typedef std::multimap<double, Order, std::greater<double>> BidOrders;//买盘
    typedef std::multimap<double, Order, std::less<double >> AskOrders;//卖盘
    void match(Order &bid, Order &ask);//买卖撮合

    std::queue<Order> m_orderUpdates;//订单更新队列
    BidOrders m_bidOrders;
    AskOrders m_askOrders;
};


#endif //CLION_MARKET_H
