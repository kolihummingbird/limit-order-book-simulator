#pragma once
#include "Order.hpp"
#include <map>
#include <queue>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <vector>

class OrderBook
{
private:
    std::map<double, std::vector<Order>, std::greater<>> bids;
    std::map<double, std::vector<Order>> asks;
    std::unordered_map<uint64_t, Order> lookup;
public:

    void addLimitOrder(Order order)
    {
        if (order.side == Side::BID) bids[order.price].push_back(order);
        else asks[order.price].push_back(order);
        lookup[order.id] = order;
        matchOrders();
    }

    void matchOrders()
    {
        while (!bids.empty() && !asks.empty())
        {
            auto& askPrice = asks.begin() -> first;
            auto& bidPrice = bids.begin() -> first;
            if (askPrice > bidPrice) break;

            auto& currentAsk = asks.begin() -> second.front();
            auto& currentBid = bids.begin() -> second.front();

            uint32_t minimal = std::min(currentBid.quantity, currentAsk.quantity);

            std::cout << "Trade | buy_id =" <<currentBid.id
                      << " sell_id=" << currentAsk.id
                      << " price=" << ask.Price
                      << " qty=" << minimal << std::endl;
            
            // Case A: Both fill
                        
            if (minimal == currentBid.quantity && minimal == currentAsk.quantity) 
            {
                uint64_t askId = currentAsk.id;
                uint64_t bidId = currentBid.id;

                asks.begin() -> second.erase(asks.begin() -> second.begin());
                if (asks.begin()->second.empty()) asks.erase(asks.begin());

                lookup.erase(askId);
                
                bids.begin() -> second.erase(bids.begin() -> second.begin());
                if (bids.begin() -> second.empty()) bids.erase(bids.begin());

                lookup.erase(bidId);
                
            }

            else
            {
                // Case B: Ask fills
                if (minimal == currentAsk.quantity)
                {
                    uint64_t askId = currentAsk.id;
                    asks.begin() -> second.erase(asks.begin() -> second.begin());
                    if (asks.begin()->second.empty()) asks.erase(asks.begin());
                    lookup.erase(askId);
                    
                    bids.begin() -> second.front().quantity -= minimal;
                }

                else
                // Case C: Bid fills
                {
                    uint64_t bidId = currentBid.id;
                    bids.begin() -> second.erase(bids.begin() -> second.begin());
                    if (bids.begin()->second.empty()) bids.erase(bids.begin());
                    lookup.erase(bidId);
                    
                    asks.begin() -> second.front().quantity -= minimal;
                }
            }

        }
    }
    
    void printBook(int depth)
    {
        int counter = 0; // counting depth
        std::cout<< "-- BIDS -- \n";
        for (auto& [price, orders] : bids)
        {
            if (depth == counter) break;
            uint32_t total = 0;
            for (auto& o : orders) total += o.quantity;
            counter++;
            std::cout << price << " " << total << std::endl;
        }

        counter = 0;
        std::cout<< "-- ASKS -- \n";
        for (auto& [price, orders] : asks)
        {
            if (depth == counter) break;
            uint32_t total = 0;
            for (auto& o : orders) total += o.quantity;
            counter++;
            std::cout << price << " " << total << std::endl;
        }
    }
};
