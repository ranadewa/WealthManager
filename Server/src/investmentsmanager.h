#pragma once
#include "investmentsrepository.h"
#include <unordered_map>
#include <string>

namespace Wealth {
    class InvestmentManager
    {
    public:
        InvestmentManager(IInvestmentRepository::IInvestmentRepositoryPtr repository);
        Investments getInvestments(std::string userID);
        bool hasInvestment(std::string userID);
        void update(std::string id, nlohmann::json const& info);


    private:
        /* data */
        std::unordered_map<std::string, Investments> _investments;
        IInvestmentRepository::IInvestmentRepositoryPtr _repository;
    };    
}