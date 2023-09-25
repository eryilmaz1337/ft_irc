/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryilmaz <eryilmaz@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:45:28 by eryilmaz          #+#    #+#             */
/*   Updated: 2023/09/16 16:45:28 by eryilmaz         ###   ########.tr	      */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAIN_HPP
# define MAIN_HPP
/*-----------COLOR------------------*/
# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define PURPLE		"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"
# define END		"\033[m"
# define RESET		"\033[0m"
/*----------------------------------*/
# include <iostream> //cout, cin, cerr
# include <sys/socket.h> // socket, setsockopt, getsockname, bind, connect, listen, accept, send, recv
# include <unistd.h> // close
# include <netdb.h> // getprotobyname, gethostbyname, freeaddrinfo, getaddrinfo
# include <arpa/inet.h> // htonl, htons, ntohs, ntohl, inet_addr, inet_ntoa,
# include <signal.h> // signal
# include <fcntl.h> // lseek, fstat, fcntl
# include <poll.h> // poll
# include <netinet/in.h> // struct sockaddr_in
# include <vector>
# include <map>
# include <functional>
# include <algorithm> // std::transform
# include <cctype>    // std::toupper
# include <string>
# include <cstring>

#endif