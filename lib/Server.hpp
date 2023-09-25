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
# include "Client.hpp"
# include "Channel.hpp"


class Server
{
	// private:
	public:
		int	port;
		int	passwd;
		int	sockfd;
		int serverClientNumber;
		int chNum;
		struct	sockaddr_in						sockAddr;
		
        std::string str;
		std::vector<struct pollfd>				pollFd;
		std::vector<Client>						clients;
		std::vector<Channel>					channels;
		std::vector<std::string>				inputs;
		std::map<std::string, void(Server::*)(Client &client)> commands;

		Server &operator=( const Server &src);
		Server( const Server &src );
		Server( char **av );
		~Server( void );

		void start( void );
		void pollIn(int i);
		void pollInElse(int i);
		void setCommands( void );
		void commands_parser(char *buffer);
		void commands_run(Client &client);

		std::string getprefix(Client &client);
		int  findChannel( void );
		void join_command( Client &client );
		void nick_command( Client &client );
		void user_command( Client &client );
		void pass_command( Client &client );
		void kick_command( Client &client );
		void part_command( Client &client );
		void ping_command( Client &client );
		void privmsg_command( Client &client );
		void notice_command( Client &client );
		void mode_command( Client &client );
		void who_command( Client &client );
		void quit_command( Client &client );
		void cap_command( Client &client );
};

#endif
