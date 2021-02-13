#pragma once
#include "investmentsrepository.h"
#include <unordered_map>
#include <string>
#include "currencyconverter.h"

namespace Wealth {
    class InvestmentManager
    {
    public:
        InvestmentManager(IInvestmentRepository::IInvestmentRepositoryPtr repository, CurrencyConverter const& converter);
        Investments getInvestments(std::string userID);
        Overview getOverview(std::string userID);
        bool hasInvestment(std::string userID);
        void update(std::string id, nlohmann::json const& info);


    private:
        /* data */
        std::unordered_map<std::string, Investments> _investments;
        IInvestmentRepository::IInvestmentRepositoryPtr _repository;
        CurrencyConverter const& _converter;
    };    
}