#pragma once
#include "user.h"
#include <vector>
#include <memory>
#include <fstream>
#include "investments.h"

using namespace std;

namespace Wealth {
    typedef std::unordered_map<std::string, Investments> UserInvestments;

        class IInvestmentRepository {
        public:
            virtual UserInvestments getInvestments() = 0;
            virtual void updateInvestment(std::string userID, Investments const& investments) = 0;

            typedef unique_ptr<IInvestmentRepository> IInvestmentRepositoryPtr;
    };

    class InvestmentsRepository : public IInvestmentRepository
    {
    public:
        InvestmentsRepository(vector<string> userIds);
        UserInvestments getInvestments() override;
        void updateInvestment(std::string userID, Investments const& investments) override;

    private:

        const vector<string> _userIds;
    };
}
