#include "investments.h"
#include <algorithm>

namespace Wealth {

    template<typename T>
    nlohmann::json transformToJson(std::vector<T> input)
    {
        nlohmann::json values = nlohmann::json::array();

        std::transform(input.begin(), input.end(), std::back_inserter(values), [](auto const& value) {
            return value.to_json();
        });

        return values;
    }

    Investments::Investments(const nlohmann::json& j)
    {

    }

    nlohmann::json Wealth::Investments::to_json() const
    {
        auto investments = nlohmann::json::array();

        std::visit([&investments, this](auto&& investment) {
            investments.push_back(investment.to_json());
        }, _investments);

        return investments;
    }

    nlohmann::json Bank::to_json() const
    {
        return nlohmann::json({ {TYPE_KEY, "bank"},
                                {CACHACCOUNT_KEY, transformToJson<Holding>(_cashAccounts)},
                                {FIXEDDEPOSIT_KEY,  transformToJson<Holding>(_fixedDeposits)} });
    }

    nlohmann::json ShareMarket::to_json() const
    {
        return nlohmann::json({ {TYPE_KEY, "shareMarket"},
                                {EQUITIES_KEY, transformToJson<Holding>(_equities)},
                                {BONDS_KEY,  transformToJson<Holding>(_bonds)},
                                {REITS_KEY,  transformToJson<Holding>(_reits)} });
    }

    nlohmann::json Property::to_json() const
    {
        return nlohmann::json({ {TYPE_KEY, "property"},
                                {COMMERCIAL_KEY, transformToJson<Holding>(_commercial)},
                                {RESIDENTIAL_KEY,  transformToJson<Holding>(_residential)},
                                {LAND_KEY,  transformToJson<Holding>(_land)} });
    }

    nlohmann::json OtherInvestments::to_json() const
    {
        return nlohmann::json({ {TYPE_KEY, "other"},
                                {OTHER_KEY, transformToJson<Holding>(_others)} });
    }

    nlohmann::json Amount::to_json() const
    {
        return nlohmann::json{ {VALUE_KEY, _value}, {CURRENCY_KEY, _currency} };
    }

    nlohmann::json Holding::to_json() const
    {      
        return nlohmann::json({ { NAME_KEY, _name }, {VALUES_KEY, transformToJson<Amount>(_values)} });
    }
}