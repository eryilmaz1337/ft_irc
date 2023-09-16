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