#pragma once

#include <string>
#include "httpserver.h"
#include "conversionrates.h"

using namespace std;

class CurrencyConverter
{

public:
    CurrencyConverter(HTTPServer& server);
    Wealth::CoversionRates getRates() const;

private:
    void update(HttpRequest request);
    Wealth::CoversionRates _rates;
    std::string _fileName;
};