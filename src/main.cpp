#include<iostream>
#include "Order.hpp"
#include "OrderBook.hpp"

int main()
{
    Order OrderOne = {1,Side::BID,Type::LIMIT, 105.75, 10, 1000};
    Order OrderTwo{2,Side::ASK,Type::MARKET, 104.25, 5, 4550};
    std::cout<< OrderOne.id << " " << static_cast<int>(OrderOne.side) <<" " << static_cast<int>(OrderOne.type) 
    << " " << OrderOne.price << " " << OrderOne.quantity << " " << OrderOne.timestamp << std::endl;

    std::cout<< OrderTwo.id << " " << static_cast<int>(OrderTwo.side) <<" " << static_cast<int>(OrderTwo.type)
    << " " << OrderTwo.price << " " << OrderTwo.quantity << " " << OrderTwo.timestamp << std::endl;

    OrderBook orderBook;

    orderBook.addLimitOrder({1, Side::ASK, Type::LIMIT, 100.0, 10, 1000});

    orderBook.addLimitOrder({2, Side::BID, Type::LIMIT, 101.0, 7, 2000});

    orderBook.printBook(5);

    orderBook.addMarketOrder({3, Side::BID, Type::MARKET, 0.0, 3, 3000});

    orderBook.printBook(5);
    
    /*
    orderBook.addLimitOrder( {1, Side::BID, Type::LIMIT, 109.7, 3, 2000});
    orderBook.addLimitOrder( {2, Side::BID, Type::LIMIT, 111.5, 7, 2000});
    orderBook.addLimitOrder( {3, Side::BID, Type::LIMIT, 105.2, 10, 2000});
    orderBook.addLimitOrder( {4, Side::BID, Type::LIMIT, 103.5, 15, 2000});
    orderBook.addLimitOrder( {5, Side::BID, Type::LIMIT, 107.0, 6, 2000});

    orderBook.addLimitOrder( {6, Side::ASK, Type::LIMIT, 111.8, 10, 2000});
    orderBook.addLimitOrder( {7, Side::ASK, Type::LIMIT, 112.0, 6, 2000});
    orderBook.addLimitOrder( {8, Side::ASK, Type::LIMIT, 117.5, 4, 2000});
    orderBook.addLimitOrder( {9, Side::ASK, Type::LIMIT, 130.0, 15, 2000});
    orderBook.addLimitOrder( {10, Side::ASK, Type::LIMIT, 115.0, 50, 2000});

    orderBook.printBook(3);
    */
}
