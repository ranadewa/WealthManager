#include "investments.h"
#include <algorithm>

namespace Wealth {
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
        return nlohmann::json();
    }

    nlohmann::json ShareMarket::to_json() const
    {
        return nlohmann::json();
    }
    nlohmann::json Property::to_json() const
    {
        return nlohmann::json();
    }

    nlohmann::json OtherInvestments::to_json() const
    {
        return nlohmann::json();
    }
}