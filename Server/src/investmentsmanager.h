#pragma once
#include "investments.h"
#include <unordered_map>
#include <string>

namespace Wealth {
    class InvestmentManager
    {
    public:
        InvestmentManager(/* args */) {};
        Investments getInvestments(std::string userID);
        bool hasInvestment(std::string userID);


    private:
        /* data */
        std::unordered_map<std::string, Investments> _investments;
    };    
}