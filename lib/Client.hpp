#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "main.hpp"

class Client
{
	public:
		int	fd;
		int	num;

		bool	passchk;
	
		std::string	nickName;
		std::string	userName;
		std::string	host;
		unsigned short port;

		Client &operator=( const Client &src);


	Client();
	Client(int fd, std::string host, unsigned short port);
	~Client();
};

#endif
