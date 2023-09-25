/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryilmaz <eryilmaz@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:43:39 by eryilmaz          #+#    #+#             */
/*   Updated: 2023/09/16 16:43:40 by eryilmaz         ###   ########.tr	      */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/Server.hpp"

Server::~Server( void )
{
	std::cout << "IRC: Server closed. Have a good day!" << std::endl;
	close(sockfd);
}

Server::Server( const Server &src )
{
	port = src.port;
	passwd = src.passwd;
	sockfd = src.sockfd;
	sockAddr = src.sockAddr;
	pollFd = src.pollFd;
	clients = src.clients;
}

Server &Server::operator=( const Server &src)
{
	port = src.port;
	passwd = src.passwd;
	sockfd = src.sockfd;
	sockAddr = src.sockAddr;
	str = src.str;
	pollFd = src.pollFd;
	clients = src.clients;
	return (*this);
}

Server::Server( char **av )
{
	setCommands();
	serverClientNumber = 0;
	chNum = 0;
	std::cout << GREEN << "IRC: Socket starting . . ." << RESET <<std::endl;
	port = std::atoi(av[1]);
	passwd = std::atoi(av[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		throw std::runtime_error("\033[0;31mError!\nSocket could not be created!\033[0m\n");
	else
		std::cout << GREEN  << "IRC: Socket created successfully!" << RESET << std::endl;
		// SILINECEK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)=/)&!'+!'^
	int val = 1;
	setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    sockAddr.sin_family = AF_INET;	//soket adresinin aile türünü belirtir. Burada AF_INET, IPv4 adres ailesini temsil eder. Sunucu, bu aile türünü kullanarak IPv4 adresleri ile iletişim kurar.
	sockAddr.sin_port = htons(port);	//sunucunun hangi port üzerinden bağlantıları dinleyeceğini belirtir. Burada htons işlevi (host to network short), 16 bitlik bir değeri ağ baytlarına (network byte order) dönüştürür. Bu nedenle 8080 portunu ağ baytlarına dönüştürerek kullanılır.
	sockAddr.sin_addr.s_addr = INADDR_ANY;	//sunucunun hangi IP adresini dinleyeceğini belirtir. INADDR_ANY, sunucunun mevcut tüm ağ arayüzleri üzerinden gelen bağlantıları kabul edeceği anlamına gelir. Bu, sunucunun herhangi bir IP adresi ile gelen bağlantıları dinlemesini sağlar ve bu şekilde sunucunun herhangi bir ağ arabirimi veya IP adresine bağlanmasına izin verir.
    std::cout << GREEN << "IRC: Socket connecting." << RESET << std::endl;
	// Sunucu soketini bağlama
    if (bind(sockfd, (struct sockaddr *)&sockAddr, sizeof(sockAddr)) == -1)
		throw std::runtime_error("\033[0;31mError!\n Bind the server socket failed\033[0m\n");
    else
        std::cout << GREEN << "IRC: Socket binded successfully!" << RESET << std::endl; 
	// Sunucu soketini dinleme
    if (listen(sockfd, 10) == -1)
		throw std::runtime_error("\033[0;31mError!\n Listening failed\033[0m\n");
    else
        std::cout << GREEN << "IRC: Expected successful connection to listening ......" << RESET << std::endl;
	std::cout << GREEN << "IRC: Listening on port " << port << RESET << std::endl;
}