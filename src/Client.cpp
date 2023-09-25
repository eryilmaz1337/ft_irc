#include "../lib/Client.hpp"

Client &Client::operator=( const Client &src)
{
	fd = src.fd;
	num = src.num;
	passchk = src.passchk;
	nickName = src.nickName;
	userName = src.userName;
	host = src.host;
	return (*this);
}

Client::Client(){

}

Client::Client(int fd, std::string host, unsigned short port){
	this->fd = fd;
	this->host = host;
	this->port = port;
}

Client::~Client(){

}