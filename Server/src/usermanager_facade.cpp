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
		auto name = utility::conversions::to_utf8string(jvalue.at(U("name")).as_string());
		auto password = utility::conversions::to_utf8string(jvalue.at(U("password")).as_string());

		auto user = _manager.authenticate(name, password);
		if (!user._id.empty())
		{
			auto result = web::json::value::object();

			result[U("name")] = web::json::value(utility::conversions::to_string_t(user._name));
			result[U("id")] = web::json::value(utility::conversions::to_string_t(user._id));
			result[U("isAdmin")] = web::json::value(user._isAdmin);

			request.reply(status_codes::OK, result);
		}
		else
		{
			request.reply(status_codes::BadRequest, U("Invalid username or password"));
		}
	});
}

void UserManagerFacade::onPasswordChange(HttpRequest request)
{
    cout << "onPasswordChange." << endl;
	parse(request, [this, request](json::value jvalue) {
		auto id = utility::conversions::to_utf8string(jvalue.at(U("id")).as_string());
		auto newPassword = utility::conversions::to_utf8string(jvalue.at(U("newPassword")).as_string());
		auto oldPassword = utility::conversions::to_utf8string(jvalue.at(U("oldPassword")).as_string());

		if (_manager.updatePassword(id, oldPassword, newPassword))
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
		auto name = utility::conversions::to_utf8string(jvalue.at(U("name")).as_string());
		auto password = utility::conversions::to_utf8string(jvalue.at(U("password")).as_string());
		auto isAdmin = jvalue.at(U("isAdmin")).as_bool();

		string error;

		User user{ name, "", password, isAdmin};

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
    cout << "getUserList." << endl;

	vector<User> users = _manager.getUsers();
	vector< web::json::value> jUsers;

	std::transform(users.begin(), users.end(), back_inserter(jUsers), [](User const& user) {
		auto userObj = web::json::value::object();

		userObj[U("name")] = web::json::value(utility::conversions::to_string_t(user._name));
		userObj[U("id")] = web::json::value(utility::conversions::to_string_t(user._id));
		userObj[U("isAdmin")] = web::json::value(user._isAdmin);

		return userObj;
	});
	

	auto result = web::json::value::array(jUsers);

	request.reply(http::status_codes::OK, result);
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
