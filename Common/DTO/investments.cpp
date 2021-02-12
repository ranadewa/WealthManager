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

    void Investments::update(nlohmann::json const& info)
    {
        if (info.find(TYPE_KEY) != info.end())
        {
            InvestmentType type;
            info.at(TYPE_KEY).get_to<InvestmentType>(type);

            for (auto& investment : _investments)
            {
                if (type == InvestmentType::BANK && std::holds_alternative<Bank>(investment))
                {
                    std::get<Bank>(investment).update(info);
                }
                else if (type == InvestmentType::SHARE_MARKET && std::holds_alternative<ShareMarket>(investment))
                {
                    std::get<ShareMarket>(investment).update(info);
                }
                else if (type == InvestmentType::PROPERTY && std::holds_alternative<Property>(investment))
                {
                    std::get<Property>(investment).update(info);
                }
                else if (type == InvestmentType::OTHER && std::holds_alternative<OtherInvestments>(investment))
                {
                    std::get<OtherInvestments>(investment).update(info);
                }
                else
                {
                    // TODO error
                }
            }
        }
    }

    Investments::Investments()
    {
        _investments.push_back(Bank());
        _investments.push_back(Property());
        _investments.push_back(ShareMarket());
        _investments.push_back(OtherInvestments());
    }

    Investments::Investments(const nlohmann::json& j)
    {
        update(j);
    }

    nlohmann::json Wealth::Investments::to_json() const
    {
        auto investments = nlohmann::json::array();

        for (auto const& current : _investments)
        {
            std::visit([&investments, this](auto&& investment) {
                investments.push_back(investment.to_json());
            }, current);
        }


        return investments;
    }

    Bank::Bank(nlohmann::json const& j)
    {
        update(j);
    }

    nlohmann::json Bank::to_json() const
    {
        return nlohmann::json({ {TYPE_KEY, "bank"},
                                {CASHACCOUNT_KEY, transformToJson(_cashAccounts._holdings)},
                                {FIXEDDEPOSIT_KEY,  transformToJson(_fixedDeposits._holdings)} });
    }

    void Bank::update(nlohmann::json const& j)
    {
        if (j.find(CATEGORY_KEY) != j.end() && j.find(Holding::NAME_KEY) != j.end())
        {
            std::string category = j[CATEGORY_KEY];
            Holdings empty{};
            Holdings& selected = (category.compare(CASHACCOUNT_KEY) == 0) ? _cashAccounts :
                (category.compare(CASHACCOUNT_KEY) == 0) ? _fixedDeposits : empty;

            selected.update(j);
        }
    }

    ShareMarket::ShareMarket(nlohmann::json const& j)
    {
    }

    nlohmann::json ShareMarket::to_json() const
    {
        return nlohmann::json({ {TYPE_KEY, "shareMarket"},
                                {EQUITIES_KEY, transformToJson(_equities._holdings)},
                                {BONDS_KEY,  transformToJson(_bonds._holdings)},
                                {REITS_KEY,  transformToJson(_reits._holdings)} });
    }

    void ShareMarket::update(nlohmann::json const& j)
    {
        if (j.find(CATEGORY_KEY) != j.end() && j.find(Holding::NAME_KEY) != j.end())
        {
            std::string category = j[CATEGORY_KEY];

            Holdings empty{};
            Holdings& selected = (category.compare(EQUITIES_KEY) == 0) ? _equities :
                                 (category.compare(BONDS_KEY) == 0) ? _bonds : 
                                 (category.compare(REITS_KEY) == 0) ? _reits : empty;

            selected.update(j);
        }
    }

    Property::Property(nlohmann::json const& j)
    {
    }

    nlohmann::json Property::to_json() const
    {
        return nlohmann::json({ {TYPE_KEY, "property"},
                                {COMMERCIAL_KEY, transformToJson(_commercial._holdings)},
                                {RESIDENTIAL_KEY,  transformToJson(_residential._holdings)},
                                {LAND_KEY,  transformToJson(_land._holdings)} });
    }

    void Property::update(nlohmann::json const& j)
    {
        if (j.find(CATEGORY_KEY) != j.end() && j.find(Holding::NAME_KEY) != j.end())
        {
            std::string category = j[CATEGORY_KEY];

            Holdings empty{};
            Holdings& selected = (category.compare(RESIDENTIAL_KEY) == 0) ? _residential :
                (category.compare(COMMERCIAL_KEY) == 0) ? _commercial :
                (category.compare(LAND_KEY) == 0) ? _land : empty;

            selected.update(j);
        }
    }

    OtherInvestments::OtherInvestments(nlohmann::json const& j)
    {
    }

    nlohmann::json OtherInvestments::to_json() const
    {
        return nlohmann::json({ {TYPE_KEY, "other"},
                                {OTHER_KEY, transformToJson(_others._holdings)} });
    }

    void OtherInvestments::update(nlohmann::json const& j)
    {
        if (j.find(CATEGORY_KEY) != j.end() && j.find(Holding::NAME_KEY) != j.end())
        {
            std::string category = j[CATEGORY_KEY];
            Holdings empty{};
            Holdings& selected = (category.compare(OTHER_KEY) == 0) ? _others : empty;

            selected.update(j);
        }
    }

    Amount::Amount(nlohmann::json const& j) : _value{ 0 }, _currency{ Currency::USD }
    {
        if (j.find(CURRENCY_KEY) != j.end())
            j.at(CURRENCY_KEY).get_to(_currency);

        if (j.find(VALUE_KEY) != j.end())
            j.at(VALUE_KEY).get_to(_value);
    }

    nlohmann::json Amount::to_json() const
    {
        return nlohmann::json{ {VALUE_KEY, _value}, {CURRENCY_KEY, _currency} };
    }

    void Holding::update(Amount const& amount)
    {
        auto iter = std::find_if(_values.begin(), _values.end(), [&amount](Amount const& amt) {
            return amt._currency == amount._currency;
        });

        if (iter != _values.end())
        {
            iter->_value += amount._value;  // update the value for the currency
        }
        else
        {
            _values.push_back(amount);
        }
    }

    nlohmann::json Holding::to_json() const
    {      
        return nlohmann::json({ { NAME_KEY, _name }, {VALUES_KEY, transformToJson(_values)} });
    }

    void Holdings::update(nlohmann::json const& j)
    {
        std::string name = j[Holding::NAME_KEY];
        Amount amount(j);

        auto iter = std::find_if(_holdings.begin(), _holdings.end(), [&name](Holding const& holding) {
            return holding._name.compare(name) == 0;
        });

        if (iter != _holdings.end()) // Update the existing holdings
        {
            iter->update(amount);
        }
        else  // add as new holding
        {
            Holding holding{ name, {amount} };
            _holdings.push_back(holding);
        }
    }
}
