#include "../../lib/Server.hpp"

void	Server::nick_command( Client &client )
{
	std::cout << "IRC: Called NICK command\n";
	for (int i = 0; i < (int)inputs.size(); i++)
	{
		std::cout << i << ": " << inputs[i] << "\n";
	}
	try
	{
		client.nickName = inputs.at(1);
		client.userName = inputs.at(2);
		client.host = inputs.at(5);
		std::string msg = ": NICK " + client.nickName + "@" + client.host;
		if(send(client.fd, msg.c_str(), sizeof(msg), 0)==-1)
			throw std::runtime_error("ERR\n");
	}
	catch(const std::out_of_range &e)
	{
		if(send(client.fd, "out_of_range", strlen("out_of_range"), 0)==-1)
			throw std::runtime_error( "out_of_range\n");
		//"461 " + prefix + " " +  command + " :Not enough parameters"
	}
}
