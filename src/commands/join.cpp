/*
Join komutu, bir istemcinin bir kanala katılmak istediğini belirten bir komuttur. Bu komutun formatı şu şekildedir:

/join #kanal_ismi
Kanal ismi, istemcinin katılmak istediği kanalın adıdır. Kanal ismi, # işaretiyle başlamalıdır.

İstemciden gelen Join komutunu yakaladıktan sonra, aşağıdaki adımları uygulamanız gerekir:

1.Kanalın var olup olmadığını kontrol edin. Kanal yoksa, oluşturun.
2.Kanalın zaten dolu olup olmadığını kontrol edin. Kanal doluysa, istemciyi kanala eklemeyin.
3.İstemciyi kanala ekleyin. Bu, kanalın kullanıcı listesine istemcinin takma adını eklemeyi içerir.
4.Kanala tüm kullanıcılara katılış bildirimi gönderin. Bu, kanalda bulunan tüm kullanıcılara, istemcinin kanala katıldığını bildiren bir mesaj göndermeyi içerir.

*/

#include "../../lib/Server.hpp"

int	Server::findChannel( void )
{
	int	index = -1;
	for (int i = 0 ; i < (int)channels.size(); i++)
	{
		if (!strncmp(inputs[1].c_str(), channels[i].chname.c_str(), inputs[1].length()))
		{
			index = i;
			return (index);
		}
	}
	return (index);
}

void	Server::join_command( Client &client )
{
	std::cout << "Client wanna join->" << client.nickName << "\n" << client.userName << "\n";
	int	index;
	// std::string joinMessage = "JOIN #a uercan";
	// send (client.fd, joinMessage.c_str(), joinMessage.length(), 0);
	// std::cout << "JOIN FONKSIYONU" << '\n';
	std::string msg = getprefix(client);
	if (inputs.size() > 3){
		std::cerr << "join ARG Error!" << std::endl;
		msg = "join args must be like this /join <channel> <channel passwd>\n";
		if(send(client.fd, msg.c_str(), msg.length(), 0)==-1)
			throw std::runtime_error("not Sended\n");
		msg.clear();
		return;
	}
	if (inputs[1][0] != '#')
		inputs[1] = '#' + inputs[1];
	index = findChannel();
	if (index > -1)
	{
		if (channels[index].passprotected == 1)
		{
			if (strncmp(inputs[2].c_str(), channels[index].chpasswd.c_str(), channels[index].chpasswd.length()))
			{
				std::cout << "join if pass check!1\n"; 
				msg = "ERROR! PLEASE JOIN WITH CHANNEL PASSWORD!\n";
				send(client.fd, msg.c_str(), msg.length(), 0);
				msg.clear();
				return;
			}
		}
		if (channels[index].maxUser == channels[index].clientnum)
		{
			if(send(client.fd, msg.c_str(), msg.length(), 0)==-1)
				throw std::runtime_error("ERROR! YOU CANNOT JOIN THIS CHANNEL USER LIMIT REACHED\n");
			return;
		}
		if (channels[index].ifp)
		{
			std::cout << "ifp == 1\n";
			if (channels[index].whitelist.empty())
			{
				msg = "ERROR! this is a invite only channel!\n";
				send(client.fd, msg.c_str(), msg.length(), 0);
				return;	
			}
			for (unsigned long int l = 0; l < channels[index].whitelist.size(); l++)
			{
				if (!strncmp(channels[index].whitelist[l].c_str(), client.nickName.c_str(), channels[index].whitelist[l].length()) && !channels[index].whitelist.empty()){
					channels[index].chnclients.push_back(client);
					channels[index].clientnum++;
					msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
					for (int j = 0; j < channels[index].clientnum; j++){
						send(channels[index].chnclients[j].fd, msg.c_str(), msg.length(), 0);
					}
					msg.clear();
					return;
				}
				else{
					msg = "ERROR! this is a invite only channel!\n";
					send(client.fd, msg.c_str(), msg.length(), 0);
					return;
				}
			}
		}
		channels[index].chnclients.push_back(client);
		channels[index].clientnum++;
		// std::cout << "Number of client in channel: " << channels[index]._clientnum << std::endl;
		msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
		for (int j = 0; j < channels[index].clientnum; j++)
		{
			if(send(channels[index].chnclients[j].fd, msg.c_str(), msg.length(), 0)==-1)
				throw std::runtime_error("Cant send\n");
		}
		return;
	}
	else
	{
		Channel newChannel(inputs[1]);
		if (inputs.size() == 2)
			newChannel.chpasswd = inputs[2];
		newChannel.chnclients.push_back(client);
		newChannel.clientnum++;
		newChannel.admin = client.nickName;
		channels.push_back(newChannel);
		chNum++;
		msg += ' ' + inputs[0] + ' ' + inputs[1] + "\r\n";
		std::cout << "Join msg: " << msg << "\n";
		if(send(client.fd, msg.c_str(), msg.length(), 0)==-1)
			throw std::runtime_error("Not Sended!\n");
		msg.clear();
	}
}

