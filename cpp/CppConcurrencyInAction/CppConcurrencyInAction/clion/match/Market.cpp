//
// Created by RS on 2019/2/13.
//

#include "Market.h"

bool Market::insert(const Order &order) {
    if(order.getM_side()==Order::buy){
        m_bidOrders.insert(BidOrders::value_type(order.getM_price(),order));
    }else{
        m_askOrders.insert(AskOrders::value_type(order.getM_price(),order));
    }
    return true;
}

void Market::erase(const Order &order) {
    std::string id=order.getM_clientId();
    if(order.getM_side()==Order::buy){
        BidOrders::iterator i;
        for( i=m_bidOrders.begin();i!=m_bidOrders.end();++i){
            if(i->second.getM_clientId()==id){
                m_bidOrders.erase(i);
                return;
            }
        }
    }else if(order.getM_side()==Order::sell){
        BidOrders::iterator i;
        for( i=m_askOrders.begin();i!=m_askOrders.end();++i){
            if(i->second.getM_clientId()==id){
                m_askOrders.erase(i);
                return;
            }
        }
    }
}

Order &Market::find(Order::Side side, std::string id) {
    if ( side == Order::buy )
    {
        BidOrders::iterator i;
        for ( i = m_bidOrders.begin(); i != m_bidOrders.end(); ++i )
            if ( i->second.getM_clientId() == id ) return i->second;
    }
    else if ( side == Order::sell )
    {
        AskOrders::iterator i;
        for ( i = m_askOrders.begin(); i != m_askOrders.end(); ++i )
            if ( i->second.getM_clientId() == id ) return i->second;
    }
    throw std::exception();
}

bool Market::match(std::queue<Order> & orders) {
    while (true){
        if(!m_bidOrders.size()||!m_askOrders.size()){//对手盘为空
            return orders.size()!=0;
        }
        BidOrders::iterator iBid=m_bidOrders.begin();
        AskOrders::iterator iAsk=m_askOrders.begin();
        if(iBid->second.getM_price()>=iAsk->second.getM_price()){
            Order& bid=iBid->second;
            Order& ask=iAsk->second;

        }
    }

}
/**
 * 按照卖方价格撮合
 * @param bid
 * @param ask
 */
void Market::match(Order &bid, Order &ask) {
    double price =ask.getM_price();
    long quantity=0;
    quantity=bid.getM_openQuantity()>ask.getM_openQuantity()?ask.getM_openQuantity():bid.getM_openQuantity();
    bid.execute(price,quantity);
    ask.execute(price,quantity);
}


