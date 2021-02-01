#pragma once
#include <string>
#include <vector>
#include <variant>
#include "nlohmann/json.hpp"

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
    
    struct Holding
    {
        std::string _name;
        std::vector<Amount> _values;
    };
    
    typedef std::vector<Holding> Holdings;

    struct Bank  {

        nlohmann::json to_json() const;

        Holdings _cashAccounts;
        Holdings _fixedDeposits;
    };

    struct ShareMarket  {
        nlohmann::json to_json() const;

        Holdings _equities;
        Holdings _bonds;
        Holdings _reits;
    };

    struct Property  {
        nlohmann::json to_json() const;

        Holdings _residential;
        Holdings _commercial;
        Holdings _land;
    };

    struct OtherInvestments {
        nlohmann::json to_json() const;

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
        nlohmann::json to_json() const;

    private:
        std::variant<Bank, ShareMarket, Property, OtherInvestments> _investments;
    }; 
}