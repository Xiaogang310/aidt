#ifndef AIDT_HTTP_HPP_
#define AIDT_HTTP_HPP_

#include "AdbaseConfig.hpp"
#include "Http/Index.hpp"
#include "Http/Config.hpp"
#include "Http/Topic.hpp"
#include "Http/Message.hpp"
#include "Http/Server.hpp"

// {{{ macros

#ifndef DECLARE_HTTP_CONTROLLER
#define DECLARE_HTTP_CONTROLLER(name) \
	    adserver::http:: name* _http##name = nullptr;
#endif
#ifndef ADSERVER_HTTP_ADD_CONTROLLER
#define ADSERVER_HTTP_ADD_CONTROLLER(name) do {\
    _http##name = new adserver::http:: name(_context);\
    _http##name->registerLocation(_http);\
} while(0)
#endif
#ifndef ADSERVER_HTTP_STOP
#define ADSERVER_HTTP_STOP(name) \
        delete _http##name;
#endif

// }}}
class Http {
public:
	Http(AdServerContext* context, adbase::http::Server* http);
	~Http();
	void addController();
	std::unordered_map<std::string, std::string> rewrite();
private:
	AdServerContext* _context;
	adbase::http::Server* _http;
	DECLARE_HTTP_CONTROLLER(Server);
	DECLARE_HTTP_CONTROLLER(Index);
	DECLARE_HTTP_CONTROLLER(Config);
	DECLARE_HTTP_CONTROLLER(Topic);
	DECLARE_HTTP_CONTROLLER(Message);

};

#endif