#include "investmentsmanager.h"

namespace Wealth {
    InvestmentManager::InvestmentManager(IInvestmentRepository::IInvestmentRepositoryPtr repository, CurrencyConverter const& converter) :
        _repository(std::move(repository)),
        _converter(converter)
    {
        _investments = _repository->getInvestments();
    }

    Investments InvestmentManager::getInvestments(std::string userID)
    {
        return _investments.at(userID);
    }

    Overview InvestmentManager::getOverview(std::string userID)
    {
        if (_investments.find(userID) != _investments.end())
        {
            
            Overview overview = _investments.at(userID).createOverview(_converter.getRates());
            overview._userName = userID;

            return overview;
        }

        return {0,0,0,0};
    }

    bool InvestmentManager::hasInvestment(std::string userID)
    {
        return _investments.find(userID) != _investments.end() ;
    }

    void InvestmentManager::update(std::string id, nlohmann::json const& info)
    {
        if (_investments.find(id) == _investments.end())
        {
            Investments inv;
            _investments.insert({ id, inv });
        }   

        _investments.at(id).update(info);
        _repository->updateInvestment(id, _investments.at(id));
    }

}