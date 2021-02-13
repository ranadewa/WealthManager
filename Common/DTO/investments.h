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

        Amount(nlohmann::json const& j);
        nlohmann::json to_json() const;

        static inline const std::string VALUE_KEY{"value"};
        static inline const std::string CURRENCY_KEY{ "currency" };
    };
    
    struct Holding
    {
        std::string _name;
        std::vector<Amount> _values;

        Holding(std::string const& name, std::vector<Amount> const& values) : _name{ name }, _values{ values } {}
        Holding(nlohmann::json const& account);
        void update(Amount const& amount);

        nlohmann::json to_json() const;

        static inline const std::string NAME_KEY{ "name" };
        static inline const std::string VALUES_KEY{ "values" };
    };
    
    struct Holdings {

        void update(nlohmann::json const& j);
        std::vector<Holding> _holdings;
    };

    struct Bank  {
        Bank(){}
        Bank(nlohmann::json const& j);
        nlohmann::json to_json() const;

        void update(nlohmann::json const& info);

        Holdings _cashAccounts;
        Holdings _fixedDeposits;

        static inline const std::string TYPE_KEY{ "type" };
        static inline const std::string CATEGORY_KEY{ "category" };
        static inline const std::string CASHACCOUNT_KEY{ "cash" };
        static inline const std::string FIXEDDEPOSIT_KEY{ "fixedDeposits" };

    };

    struct ShareMarket  {
        ShareMarket() {}
        ShareMarket(nlohmann::json const& j);
        nlohmann::json to_json() const;

        void update(nlohmann::json const& j);

        Holdings _equities;
        Holdings _bonds;
        Holdings _reits;

        static inline const std::string TYPE_KEY{ "type" };
        static inline const std::string CATEGORY_KEY{ "category" };
        static inline const std::string EQUITIES_KEY{ "equities" };
        static inline const std::string BONDS_KEY{ "bonds" };
        static inline const std::string REITS_KEY{ "reits" };

    };

    struct Property  {
        Property() {}
        Property(nlohmann::json const& j);
        nlohmann::json to_json() const;
        
        void update(nlohmann::json const& j);

        Holdings _residential;
        Holdings _commercial;
        Holdings _land;

        static inline const std::string TYPE_KEY{ "type" };
        static inline const std::string CATEGORY_KEY{ "category" };
        static inline const std::string RESIDENTIAL_KEY{ "residential" };
        static inline const std::string COMMERCIAL_KEY{ "commercial" };
        static inline const std::string LAND_KEY{ "land" };
    };

    struct OtherInvestments {
        OtherInvestments() {}
        OtherInvestments(nlohmann::json const& j);
        nlohmann::json to_json() const;
        void update(nlohmann::json const& j);

        bool _invalid{ false };
        Holdings _others;

        static inline const std::string TYPE_KEY{ "type" };
        static inline const std::string CATEGORY_KEY{ "category" };
        static inline const std::string OTHER_KEY{ "other" };
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
        using InvestmentVariant = std::variant<Bank, ShareMarket, Property, OtherInvestments>;
        Investments(const nlohmann::json& j);
        nlohmann::json to_json() const;
        void update(nlohmann::json const& info);
        static inline const std::string TYPE_KEY{ "type" };
        static inline const std::string CATEGORY_KEY{ "category" };
    private:
        std::vector<InvestmentVariant> _investments;
        
    }; 
}
