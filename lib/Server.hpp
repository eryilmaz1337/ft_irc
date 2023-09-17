/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryilmaz <eryilmaz@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:50:23 by eryilmaz          #+#    #+#             */
/*   Updated: 2023/08/28 13:50:39 by eryilmaz         ###   ########.tr	      */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
# include "main.hpp"

class Server
{
	public:
		int	_port;
		int	_passwd;
		int	_sockfd;
		int	_chNum;
		int	_srvClientNum;

		struct sockaddr_in						_sockAddr;
		
        char	buffer[1024];
		//std::vector<std::string>				inputs;
		// std::vector<Client>						clients;
		std::vector<struct pollfd>						pollFd;
		//std::map<std::string, void(Server::*)(Client &client)> commands;
		// std::vector<Channel>					channels;

		Server &operator=( const Server &src);
		Server( const Server &src );
		Server( char **av );
		~Server( void );

		void Start( void );
		void Commands(int clientFd, std::string command);

};

# endif
