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
	std::cout << GREEN << "IRC: Socket starting . . ." << RESET <<std::endl;
	_port = std::atoi(av[1]);
	_passwd = std::atoi(av[2]);
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	// _srvClientNum = 0;
	// _chNum = 0;
	if (_sockfd == -1)
		throw std::runtime_error("\033[0;31mError!\nSocket could not be created!\033[0m\n");
	else
		std::cout << GREEN  << "IRC: Socket created successfully!" << RESET << std::endl;
    _sockAddr.sin_family = AF_INET;	//soket adresinin aile türünü belirtir. Burada AF_INET, IPv4 adres ailesini temsil eder. Sunucu, bu aile türünü kullanarak IPv4 adresleri ile iletişim kurar.
	_sockAddr.sin_port = htons(_port);	//sunucunun hangi port üzerinden bağlantıları dinleyeceğini belirtir. Burada htons işlevi (host to network short), 16 bitlik bir değeri ağ baytlarına (network byte order) dönüştürür. Bu nedenle 8080 portunu ağ baytlarına dönüştürerek kullanılır.
	_sockAddr.sin_addr.s_addr = INADDR_ANY;	//sunucunun hangi IP adresini dinleyeceğini belirtir. INADDR_ANY, sunucunun mevcut tüm ağ arayüzleri üzerinden gelen bağlantıları kabul edeceği anlamına gelir. Bu, sunucunun herhangi bir IP adresi ile gelen bağlantıları dinlemesini sağlar ve bu şekilde sunucunun herhangi bir ağ arabirimi veya IP adresine bağlanmasına izin verir.
    std::cout << GREEN << "IRC: Socket connecting." << RESET << std::endl;
	// Sunucu soketini bağlama
    if (bind(_sockfd, (struct sockaddr *)&_sockAddr, sizeof(_sockAddr)) == -1)
		throw std::runtime_error("\033[0;31mError!\n Bind the server socket failed\033[0m\n");
    else
        std::cout << GREEN << "IRC: Socket binded successfully!" << RESET << std::endl; 
	// Sunucu soketini dinleme
    if (listen(_sockfd, 10) == -1)
		throw std::runtime_error("\033[0;31mError!\n Listening failed\033[0m\n");
    else
        std::cout << GREEN << "IRC: Expected successful connection to listening ......" << RESET << std::endl;
	std::cout << GREEN << "IRC: Listening on port " << _port << RESET << std::endl;
}

void Server::Start(void)
{
	int accept_fd;
	struct sockaddr_in client_addr;
	struct pollfd serverPoll;
   	socklen_t client;
	client = sizeof(client_addr);
    serverPoll.fd = _sockfd;
    serverPoll.events = POLLIN;
    pollFd.push_back(serverPoll);
	while(1)
	{
		int pollResult = poll(pollFd.data(), pollFd.size(), -1); // Sonsuz süre beklemek için -1 kullanılır
        if (pollResult == -1)
			throw std::runtime_error("\033[0;31mError!\n Polling failed\033[0m\n");
		for (size_t i = 0; i < pollFd.size(); i++) 
		{
            if (pollFd[i].revents == POLLIN) 
			{
				// Veri alımı için olay kontrolü
                if (pollFd[i].fd == _sockfd) 
				{ // Yeni bir bağlantı isteği varsa
                    accept_fd= accept(_sockfd, (struct sockaddr*)&client_addr, &client);
                    if (accept_fd == -1) 
					{
						std::cerr << RED << "IRC: Connection failed" << RESET << std::endl;
						goto end;
                    }
                    // Yeni soketi dinlemeye ekle
                    struct pollfd newPoll;
                    newPoll.fd = accept_fd;
                    newPoll.events = POLLIN;
                    pollFd.push_back(newPoll);
                } 
				else 
				{ // Mevcut bir soket üzerinden veri alınıyor
                    ssize_t bytesRead = recv(pollFd[i].fd, buffer, sizeof(buffer), 0);
                    if (bytesRead <= 0)
					{
                        if (bytesRead == 0)
                            std::cout << GREEN << "Connection closed: " << pollFd[i].fd << RESET << std::endl;
						else
							std::cerr << RED << "IRC: Message could not be received" << RESET << std::endl;
                        // Soketi kapat
                        close(pollFd[i].fd);
                        pollFd.erase(pollFd.begin() + i); // pollFd listesinden kaldır
                        i--; // Endeks güncelleme
                    } 
					else 
					{
                        // Alınan veriyi işleme devam et
                        buffer[bytesRead] = '\0'; // Null-terminate C string
                        std::cout << GREEN << "Received data (" << pollFd[i].fd << "): " << buffer << RESET << std::endl;
						//Commands(i, buffer);
					}
				}
				end:;
			}
		}
	}
	close(_sockfd);

}

// void	Server::setCommands()
// {
// 	commands["QUIT"] = &Server::quit_command;
// 	commands["CAP"] = &Server::cap_command;
// 	commands["USER"] = &Server::user_command;
// 	commands["JOIN"] = &Server::join_command;
// 	commands["QUIT"] = &Server::quit_command;
// 	commands["NICK"] = &Server::nick;
// 	commands["PASS"] = &Server::pass;
// 	commands["USER"] = &Server::user;
// 	commands["KICK"] = &Server::kick;
// 	commands["PART"] = &Server::part;
// 	commands["PING"] = &Server::ping;
// 	commands["PRIVMSG"] = &Server::privmsg;
// 	commands["NOTICE"] = &Server::notice;
// 	commands["MODE"] = &Server::mode;
// 	commands["WHO"] = &Server::who;
// }

// void Server::Commands(int clientFd, str::starting )
// {

// 	//burda kaldık komutların işleniş yapısı belirlenecek
// }