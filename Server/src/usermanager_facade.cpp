#include "usermanager_facade.h"
#include <functional>
#include <algorithm>
#include <iterator>
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

	parse(request, [this, request](json::value jvalue) {

		nlohmann::json object = nlohmann::json::parse(utility::conversions::to_utf8string(jvalue.serialize()));
		User user{ object };

		if (_manager.authenticate(user))
		{
			request.reply(status_codes::OK, user.to_json().dump());
		}
		else
		{
			request.reply(status_codes::Unauthorized, U("Invalid username or password"));
		}
	});
}

void UserManagerFacade::onPasswordChange(HttpRequest request)
{
    cout << "onPasswordChange." << endl;
	parse(request, [this, request](json::value jvalue) {

		nlohmann::json object = nlohmann::json::parse(utility::conversions::to_utf8string(jvalue.serialize()));
		User user{ object };

		auto newPassword = utility::conversions::to_utf8string(jvalue.at(U("newPassword")).as_string());

		if (_manager.updatePassword(user, newPassword))
		{
			request.reply(status_codes::OK);
		}
		else
		{
			request.reply(status_codes::BadRequest, U("Invalid username or password"));
		}
	});
}

void UserManagerFacade::add(HttpRequest request)
{
	parse(request, [this, request](json::value jvalue) {
		
		nlohmann::json object = nlohmann::json::parse(utility::conversions::to_utf8string(jvalue.serialize()));

		string error;

		User user{ object };

		if (_manager.addUser(std::move(user), error))
		{
			request.reply(status_codes::OK);
		}
		else
		{
			request.reply(status_codes::BadRequest, error.c_str());
		}
	});
}

void UserManagerFacade::deleteUser(HttpRequest request)
{
    cout << "deleteUser." << endl;
}

void UserManagerFacade::getUserList(HttpRequest request)
{
	vector<User> users = _manager.getUsers();
	auto jUsers = nlohmann::json::array();

	std::transform(users.begin(), users.end(), back_inserter(jUsers), [](User const& user) {

		return user.to_json();
	});
	
	request.reply(http::status_codes::OK, jUsers.dump());
}

void UserManagerFacade::parse(HttpRequest request, function<void(json::value)> out)
{

		request
		.extract_json()
		.then([this, request, out](pplx::task<json::value> task) {
		try
		{

			auto const& jvalue = task.get();

			if (!jvalue.is_null())
			{
				out(jvalue);
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
