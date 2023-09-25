#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "main.hpp"
#include "Client.hpp"

class Client;

class Channel
{
public:
	std::string					chname;
	std::string					chpasswd;
	std::string					admin;
	std::vector<std::string>	whitelist;
	std::vector<Client>			chnclients;
	int							maxUser;
	int							passprotected;
	int							clientnum;
	bool						ifn;
	bool						ifp;

	Channel(std::string name) : chname(name) {clientnum = 0; passprotected = 0; maxUser = 0; ifn = 0; ifp = 0;};
};

#endif