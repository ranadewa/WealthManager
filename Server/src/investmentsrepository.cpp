#include "investmentsrepository.h"

namespace Wealth {
    InvestmentsRepository::InvestmentsRepository(vector<string> userIds) :
        _userIds(userIds)
    {

    }
    UserInvestments InvestmentsRepository::getInvestments()
    {
        UserInvestments userInvestments;

        for (auto const& id : _userIds)
        {
            auto fileName = id + std::string("_investments.json");
            ifstream investmentFile(fileName, ifstream::in);

            if (investmentFile.good()) // file exist
            {
                nlohmann::json investment = nlohmann::json::parse(investmentFile);
                
                Investments userInvestment(investment);
                
                userInvestments.insert({ id, std::move(userInvestment) });
            }
        }

        return userInvestments;
    }

    void InvestmentsRepository::updateInvestment(std::string userID, Investments const& investments)
    {
        auto fileName = userID + std::string("_investments.json");

        ofstream investmentFile(fileName, ofstream::trunc);

        investmentFile << investments.to_json();
    }
}
