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
	close(_sockfd);
}

Server::Server( char **av )
{
	std::cout << "IRC: Socket starting . . ." << std::endl;
	_port = std::atoi(av[1]);
	_passwd = std::atoi(av[2]);
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// _srvClientNum = 0;
	// _chNum = 0;
	if (_sockfd == -1)
		throw std::runtime_error("Error!\nSocket could not be created!\n");
	else
		std::cout << "IRC: Socket created successfully!\n";
    _sockAddr.sin_family = AF_INET;	//soket adresinin aile türünü belirtir. Burada AF_INET, IPv4 adres ailesini temsil eder. Sunucu, bu aile türünü kullanarak IPv4 adresleri ile iletişim kurar.
	_sockAddr.sin_port = htons(_port);	//sunucunun hangi port üzerinden bağlantıları dinleyeceğini belirtir. Burada htons işlevi (host to network short), 16 bitlik bir değeri ağ baytlarına (network byte order) dönüştürür. Bu nedenle 8080 portunu ağ baytlarına dönüştürerek kullanılır.
	_sockAddr.sin_addr.s_addr = INADDR_ANY;	//sunucunun hangi IP adresini dinleyeceğini belirtir. INADDR_ANY, sunucunun mevcut tüm ağ arayüzleri üzerinden gelen bağlantıları kabul edeceği anlamına gelir. Bu, sunucunun herhangi bir IP adresi ile gelen bağlantıları dinlemesini sağlar ve bu şekilde sunucunun herhangi bir ağ arabirimi veya IP adresine bağlanmasına izin verir.
    std::cout << "IRC: Socket connecting.\n";
	// Sunucu soketini bağlama
    if (bind(_sockfd, (struct sockaddr *)&_sockAddr, sizeof(_sockAddr)) == -1)
		throw std::runtime_error("Error!\n Bind the server socket failed\n");
    else
        std::cout << "IRC: Socket binded successfully!\n";
    if (listen(_sockfd, 10) == -1)
		throw std::runtime_error("Error!\n Listening failed\n");
    else
        std::cout << "IRC: Expected successful connection to listening ......n";
	std::cout << "IRC: Listening on port " << _port << std::endl;
}

void	Server::start( void )
{
    connection();
	close(_sockfd);
}

void Server::connection(void)
{
    int client_fd;
    sockaddr_in client_addr;
    do
    {
        client_fd = accept(_sockfd, (struct sockaddr*)& , NULL);
    }while(1);
}