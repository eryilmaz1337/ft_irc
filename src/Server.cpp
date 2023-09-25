#include "../lib/Server.hpp"

std::string Server::getprefix(Client &client)
{
	std::string ret;
	ret = ':' + client.nickName + '!' + client.userName;
	if (!client.host.empty())
		ret += '@' + client.host;
	return (ret);
}

void Server::pollIn(int i)
{
	struct sockaddr_in client_addr;
	socklen_t client;
	int accept_fd;
	client = sizeof(client_addr);
	if (pollFd[i].revents == POLLIN) 
	{
		// Veri alımı için olay kontrolü
        if (pollFd[i].fd == sockfd) 
		{ // Yeni bir bağlantı isteği varsa
            accept_fd= accept(sockfd, (struct sockaddr*)&client_addr, &client);
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
			Client newClient = Client(accept_fd, "asdad", 6666);
            // client i havuza ekleme
			clients.push_back(newClient);
			serverClientNumber++;
        } 
		else  // Mevcut bir soket üzerinden veri alınıyor
           pollInElse(i);
		end:;
	}
}

void Server::pollInElse(int i)
{
	char buffer[1024];
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
        std::cout << GREEN << "Received data (" << pollFd[i].fd << "): '" << buffer << "'" << RESET << std::endl;
		// commands_parser(buffer);
		// commands_run(clients[i - 1]);
	}
}

void Server::commands_parser(char *buffer)
{
	int	i;

	i = 0;
	char* str = strtok(buffer, " \n");
	while (str != NULL)
	{
		inputs.push_back(str);
		i++;
		str = strtok(NULL, " \n");
	}
}

void Server::commands_run(Client &client)
{
	for(unsigned long int i = 0; i < inputs.size(); i++)
	{
		std::map<std::string, void(Server::*)(Client &client)>::iterator itCF;
		std::cout << "get command :" << inputs[i] << std::endl;
		for (itCF = commands.begin(); itCF != commands.end(); ++itCF)
		{
			if (!itCF->first.compare(inputs[i]))
			{
				(this->*(itCF->second))(client);
			}
		}
	}
	inputs.clear();
}

void Server::start(void)
{
	struct	pollfd	ServerPoll;
    ServerPoll.fd = sockfd;
    ServerPoll.events = POLLIN;
    pollFd.push_back(ServerPoll);
	while(1)
	{
		int pollResult = poll(pollFd.data(), pollFd.size(), -1); // Sonsuz süre beklemek için -1 kullanılır
        if (pollResult == -1)
			throw std::runtime_error("\033[0;31mError!\n Polling failed\033[0m\n");
		for (size_t i = 0; i < pollFd.size(); i++) 
		{
			pollIn(i);
		}
	}
	close(sockfd);
}

void	Server::setCommands(void)
{
	commands["QUIT"]	= &Server::quit_command;	//hazır fonksiyon
	commands["CAP"] 	= &Server::cap_command; 	//hazır fonksiyon
	commands["USER"]	= &Server::user_command;	//hazır fonksiyon
	commands["JOIN"]	= &Server::join_command;	//hazır fonksiyon
	commands["NICK"]	= &Server::nick_command;			//hazır fonksiyon düzeltilicek
	commands["PASS"]	= &Server::pass_command;			//hazır fonksiyon düzeltilicek
	//commands["KICK"]	= &Server::kick_command;			//yok umut
	//commands["PART"]	= &Server::part_command;			//yok umut
	commands["PING"]	= &Server::ping_command;			//hazır fonksiyon
	commands["PRIVMSG"]	= &Server::privmsg_command;			//yapılıyor umut
	//commands["NOTICE"]	= &Server::notice_command;			//yok erdem
	//commands["MODE"]	= &Server::mode_command;			//yok erdem
	//commands["WHO"]		= &Server::who_command;				//yok erdem
}