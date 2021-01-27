#pragma once
#include "investments.h"
#include <unordered_map>

namespace Wealth {
    class InvestmentManager
    {
    public:
        InvestmentManager(/* args */);
        ~InvestmentManager();
    private:
        /* data */
        std::unordered_map<InvestmentType, Investments> _investments;
    };    
}