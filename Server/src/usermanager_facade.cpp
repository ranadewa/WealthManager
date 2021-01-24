#include "usermanager_facade.h"
#include <functional>
#include "uri.h"

UserManagerFacade::UserManagerFacade(HTTPServer& server, UserManager& manager): _manager(manager)
{
    server.registerEndpoint(methods::PUT, URI::authenticate, std::bind(&UserManagerFacade::onAuthRequest, this, std::placeholders::_1));
    server.registerEndpoint(methods::POST, URI::changepassword, std::bind(&UserManagerFacade::onPasswordChange, this, std::placeholders::_1));
    server.registerEndpoint(methods::POST, URI::user, std::bind(&UserManagerFacade::add, this, std::placeholders::_1));
    server.registerEndpoint(methods::DEL, URI::user, std::bind(&UserManagerFacade::deleteUser, this, std::placeholders::_1));
    server.registerEndpoint(methods::GET, URI::user, std::bind(&UserManagerFacade::getUserList, this, std::placeholders::_1));
}

void UserManagerFacade::onAuthRequest(HttpRequest request)
{
    cout << "on Auth request received." << endl;

		request
			.extract_json()
			.then([this, request](pplx::task<json::value> task) {
			try
			{

				auto const& jvalue = task.get();

				if (!jvalue.is_null())
				{
					auto name = utility::conversions::to_utf8string(jvalue.at(U("name")).as_string());
					auto password = utility::conversions::to_utf8string(jvalue.at(U("password")).as_string());

					auto id = _manager.authentiate(name, password);
					if (!id.empty())
					{
						request.reply(status_codes::OK);
					}
					else
					{
						request.reply(status_codes::BadRequest, U("Invalid username or password"));
					}
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

void UserManagerFacade::onPasswordChange(HttpRequest request)
{
    cout << "onPasswordChange." << endl;
}

void UserManagerFacade::add(HttpRequest request)
{
    cout << "add." << endl;
}

void UserManagerFacade::deleteUser(HttpRequest request)
{
    cout << "deleteUser." << endl;
}

void UserManagerFacade::getUserList(HttpRequest request)
{
    cout << "getUserList." << endl;
}
