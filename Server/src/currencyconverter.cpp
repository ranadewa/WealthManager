#include "currencyconverter.h"
#include "uri.h"
#include <fstream>
#include "nlohmann/json.hpp"

using namespace std;

CurrencyConverter::CurrencyConverter(HTTPServer& server) : _fileName{"usd_conversions.json"}
{
    server.registerEndpoint(http::methods::POST, URI::currency, std::bind(&CurrencyConverter::update, this, std::placeholders::_1));

    ifstream currencyFile(_fileName, ifstream::in);

    nlohmann::json object;
    if (!currencyFile.good()) // file doesnt exist
    {
        ofstream file(_fileName, ofstream::trunc); // create
        file << _rates.to_json();
    }
    else
    {
        currencyFile >> object;
        _rates.init(object);
    }
}

Wealth::CoversionRates  CurrencyConverter::getRates() const
{
    return _rates;
}

void CurrencyConverter::update(HttpRequest request)
{
    request
        .extract_json()
        .then([this, request](pplx::task<json::value> task) {
        try
        {

            auto const& jvalue = task.get();

            if (!jvalue.is_null())
            {
                nlohmann::json object = nlohmann::json::parse(utility::conversions::to_utf8string(jvalue.serialize()));
                std::cout << object;

                _rates.update(object);

                ofstream file(_fileName, ofstream::trunc);
                file << _rates.to_json();
            }
        }
        catch (http_exception const& e)
        {
            request.reply(status_codes::InternalError, U("Internal Server Error"));
            std::cout << e.what() << endl;
        }
    })
        .wait();
}
