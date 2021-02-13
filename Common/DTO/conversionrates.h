#pragma once

#include<string>
#include<unordered_map>
#include"nlohmann/json.hpp"

namespace Wealth {

    enum class Currency
    {
        USD, // US Dollar
        SGD, // Singapore Dollar
        LKR  // Sri Lankan Rupee
    };

    // Converstion rates wrt USD
    struct CoversionRates {

        CoversionRates()
        {
            auto object = nlohmann::json({ {Wealth::Currency::SGD, 1.32}, {Wealth::Currency::LKR, 180} }); // Write Defaults
            init(object);
        }

        void init(nlohmann::json const& object)
        {
            auto iter = object.begin();
            auto end = object.end();

            while (iter != end)
            {
                auto values = *iter;
                Wealth::Currency currency = values[0];
                double rate = values[1];

                _rateMap.insert({ currency, rate });
                ++iter;
            }
        }

        double getRate(Currency currency) const
        {
            return _rateMap.at(currency);
        }

        void update(nlohmann::json const& object)
        {
            if (object.find(CURRENCY_KEY) != object.end() &&
                object.find(VALUE_KEY) != object.end())
            {
                Wealth::Currency currency = object[CURRENCY_KEY];
                double value = object[VALUE_KEY];

                _rateMap[currency] = value;
            }
        }

        nlohmann::json to_json() const
        {
            return nlohmann::json(_rateMap);
        }

        std::unordered_map<Currency, double> _rateMap;

        static inline const std::string CURRENCY_KEY{ "currency" };
        static inline const std::string VALUE_KEY{ "value" };
    };
}
