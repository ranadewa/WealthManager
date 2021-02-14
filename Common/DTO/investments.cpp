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

    void setValuesFromObject(std::string const& key, nlohmann::json const& object, Holdings& holdings)
    {
        if (object.find(key) != object.end())
        {
            auto accounts = object.at(key);

            std::transform(accounts.begin(), accounts.end(), std::back_inserter(holdings._holdings), [](nlohmann::json const& account) {
                return Holding(account);
            });
        }
    }

    Overview Investments::createOverview(CoversionRates conversions)
    {
        double bank = 0, shares = 0, properties = 0, other = 0;

        for (auto& investment : _investments)
        {
            if (std::holds_alternative<Bank>(investment))
            {
                bank = std::get<Bank>(investment).total(conversions);
            }
            else if (std::holds_alternative<ShareMarket>(investment))
            {
                shares = std::get<ShareMarket>(investment).total(conversions);
            }
            else if (std::holds_alternative<Property>(investment))
            {
                properties = std::get<Property>(investment).total(conversions);
            }
            else if (std::holds_alternative<OtherInvestments>(investment))
            {
                other = std::get<OtherInvestments>(investment).total(conversions);
            }
        }
        
        return Overview(bank, shares, properties, other);
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
        auto iter = j.begin();
        auto end = j.end();

        while (iter != end)
        {
            auto info = *iter;

            if (info.find(TYPE_KEY) != info.end())
            {
                InvestmentType type;
                info.at(TYPE_KEY).get_to<InvestmentType>(type);

                switch (type)
                {
                case Wealth::InvestmentType::BANK:
                    _investments.push_back(Bank(info));
                    break;
                case Wealth::InvestmentType::SHARE_MARKET:
                    _investments.push_back(ShareMarket(info));
                    break;
                case Wealth::InvestmentType::PROPERTY:
                    _investments.push_back(Property(info));
                    break;
                case Wealth::InvestmentType::OTHER:
                    _investments.push_back(OtherInvestments(info));
                    break;
                default:
                    break;
                }
            }

            ++iter;
        }
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
        setValuesFromObject(CASHACCOUNT_KEY, j, _cashAccounts);
        setValuesFromObject(FIXEDDEPOSIT_KEY, j, _fixedDeposits);
    }

    nlohmann::json Bank::to_json() const
    {
        return nlohmann::json({ {TYPE_KEY, InvestmentType::BANK},
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
                (category.compare(FIXEDDEPOSIT_KEY) == 0) ? _fixedDeposits : empty;

            selected.update(j);
        }
    }

    double Bank::total(CoversionRates const& conversion)
    {
        double total = _cashAccounts.total(conversion) + _fixedDeposits.total(conversion);

        return total;
    }

    ShareMarket::ShareMarket(nlohmann::json const& j)
    {
        setValuesFromObject(EQUITIES_KEY, j, _equities);
        setValuesFromObject(BONDS_KEY, j, _bonds);
        setValuesFromObject(REITS_KEY, j, _reits);
    }

    nlohmann::json ShareMarket::to_json() const
    {
        return nlohmann::json({ {TYPE_KEY, InvestmentType::SHARE_MARKET},
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

    double ShareMarket::total(CoversionRates const& conversion)
    {
        return _equities.total(conversion) + _bonds.total(conversion) + _reits.total(conversion);
    }

    Property::Property(nlohmann::json const& j)
    {
        setValuesFromObject(COMMERCIAL_KEY, j, _commercial);
        setValuesFromObject(RESIDENTIAL_KEY, j, _residential);
        setValuesFromObject(LAND_KEY, j, _land);
    }

    nlohmann::json Property::to_json() const
    {
        return nlohmann::json({ {TYPE_KEY, InvestmentType::PROPERTY},
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

    double Property::total(CoversionRates const& conversion)
    {
        return _commercial.total(conversion) + _residential.total(conversion) + _land.total(conversion);
    }

    OtherInvestments::OtherInvestments(nlohmann::json const& j)
    {
        setValuesFromObject(OTHER_KEY, j, _others);
    }

    nlohmann::json OtherInvestments::to_json() const
    {
        return nlohmann::json({ {TYPE_KEY, InvestmentType::OTHER},
                                {OTHER_KEY, transformToJson(_others._holdings)} });
    }

    void OtherInvestments::update(nlohmann::json const& j)
    {
        if (j.find(CATEGORY_KEY) != j.end() && j.find(Holding::NAME_KEY) != j.end())
        {
            _others.update(j);
        }
    }

    double OtherInvestments::total(CoversionRates const& conversion)
    {
        return _others.total(conversion);
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

    Holding::Holding(nlohmann::json const& account)
    {
        if (account.find(NAME_KEY) != account.end())
            account.at(NAME_KEY).get_to(_name);

        if (account.find(VALUES_KEY) != account.end())
        {
            auto values = account.at(VALUES_KEY);
            
            std::transform(values.begin(), values.end(), std::back_inserter(_values), [](nlohmann::json const& amount) {
                return Amount(amount);
            });
        }
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

    double Holding::total(CoversionRates const& conversion) const
    {
        double total{ 0 };

        for (auto const& amount : _values)
        {
            total += (amount._currency == Currency::USD) ? amount._value : (amount._value / conversion.getRate(amount._currency));
        }

        return total;
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

    double Holdings::total(CoversionRates const& conversion)
    {
        double total{ 0 };

        for (auto const& account : _holdings)
        {
            total += account.total(conversion);
        }

        return total;
    }

    Overview::Overview(double bank, double shares, double properties, double others):
        _totalBank(bank), _totalShareMarket(shares), _totalProperty(properties), _totalOther(others)
    {
        _netWorth = _totalBank + _totalShareMarket + _totalProperty + _totalOther;
    }

    nlohmann::json Overview::to_json() const
    {
        return nlohmann::json({
            {NAME_KEY , _userName},
            {BANK_KEY, _totalBank}, {SHARES_KEY, _totalShareMarket}, {PROPERTIES_KEY, _totalProperty}, {OTHERS_KEY, _totalOther},
            {NETWORTH_KEY, _netWorth}
            });
    }
}
