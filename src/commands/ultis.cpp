
#include "../../lib/Client.hpp"
std::string getprefix(Client &client)
{
	std::string ret;
	ret = ':' + client.nickName + '!' + client.userName;
	if (!client.host.empty())
		ret += '@' + client.host;
	return (ret);
}

