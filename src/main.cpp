/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eryilmaz <eryilmaz@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:49:46 by eryilmaz          #+#    #+#             */
/*   Updated: 2023/08/28 13:49:47 by eryilmaz         ###   ########.tr	      */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/Server.hpp"

int main(int index __attribute((unused)), char **str)
{
    if(str[1] == NULL || str[2] == NULL)
    {
        std::cerr << RED << "Usage: ./ircserv [port] [password]" << RESET << std::endl;
        return (1);
    }
    Server main_server(str);
    main_server.start();
    return (0);
}