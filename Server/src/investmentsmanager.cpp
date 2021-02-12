#include "investmentsmanager.h"

namespace Wealth {
    InvestmentManager::InvestmentManager(IInvestmentRepository::IInvestmentRepositoryPtr repository) :
        _repository(std::move(repository))
    {
        _investments = _repository->getInvestments();
    }

    Investments InvestmentManager::getInvestments(std::string userID)
    {
        return _investments.at(userID);
    }

    bool InvestmentManager::hasInvestment(std::string userID)
    {
        return _investments.find(userID) != _investments.end() ;
    }

    void InvestmentManager::update(std::string id, nlohmann::json const& info)
    {
        if (_investments.find(id) != _investments.end())
        {
            _investments.at(id).update(info);
        }
        else
        {
            Investments inv;
            inv.update(info);
            _investments.insert({ id, inv });
        }
    }

}