#pragma once
#include <string>
#include <vector>

namespace Wealth {
    typedef double price;

    enum class Currency
    {
        USD, // US Dollar
        SGD, // Singapore Dollar
        LKR  // Sri Lankan Rupee
    };

    struct Amount
    {
        price _value;
        Currency _currency;
    };
    
    struct Instrument
    {
        std::string _name;
        std::vector<Amount> _values;
    };
    

    enum class InvestmentType
    {
        BANK,
        SHARE_MARKET,
        PROPERTY,
        OTHER
    };

    class Investments
    {
    public:
        Investments();

    private:
        std::vector<Instrument> _investments;
    }; 
}