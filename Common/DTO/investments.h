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

        nlohmann::json to_json() const;

    private:
        const std::string VALUE_KEY{"value"};
        const std::string CURRENCY_KEY{ "currency" };
    };
    
    struct Holding
    {
        std::string _name;
        std::vector<Amount> _values;

        nlohmann::json to_json() const;

    private:
        const std::string NAME_KEY{ "name" };
        const std::string VALUES_KEY{ "values" };
    };
    
    typedef std::vector<Holding> Holdings;

    struct Bank  {

        nlohmann::json to_json() const;

        Holdings _cashAccounts;
        Holdings _fixedDeposits;

        static inline const std::string TYPE_KEY{ "type" };
    private:
        const std::string CACHACCOUNT_KEY{ "cashAccounts" };
        const std::string FIXEDDEPOSIT_KEY{ "fixedDeposits" };
    };

    struct ShareMarket  {
        nlohmann::json to_json() const;

        Holdings _equities;
        Holdings _bonds;
        Holdings _reits;

        static inline const std::string TYPE_KEY{ "type" };
    private:
        const std::string EQUITIES_KEY{ "equities" };
        const std::string BONDS_KEY{ "bonds" };
        const std::string REITS_KEY{ "reits" };
    };

    struct Property  {
        nlohmann::json to_json() const;

        Holdings _residential;
        Holdings _commercial;
        Holdings _land;

        static inline const std::string TYPE_KEY{ "type" };
    private:
        const std::string RESIDENTIAL_KEY{ "residential" };
        const std::string COMMERCIAL_KEY{ "commercial" };
        const std::string LAND_KEY{ "land" };
    };

    struct OtherInvestments {
        nlohmann::json to_json() const;

        Holdings _others;

        static inline const std::string TYPE_KEY{ "type" };
    private:
        const std::string OTHER_KEY{ "other" };
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
        Investments(const nlohmann::json& j);
        nlohmann::json to_json() const;

    private:
        std::variant<Bank, ShareMarket, Property, OtherInvestments> _investments;
    }; 
}