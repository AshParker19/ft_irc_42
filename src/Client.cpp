/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 22:55:40 by anshovah          #+#    #+#             */
/*   Updated: 2024/05/04 06:11:36 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "utils.hpp"

Client::Client(const int socketFd) : _socketFd(socketFd)
{
	info ("Created Client Inctance", CLR_BLU);
}

Client::~Client()
{
		std::list<Channel *>::iterator it = _channels.begin();

		while (it != _channels.end())
		{
				(*it)->removeClient(this);
				it++;
		}
		_channels.clear();
	// Client::_nicknames.erase(_nickname);
}

bool	Client::appendBuffer(const char *buffer)
{
	_inputBuffer += std::string(buffer);
	if (_inputBuffer.size() > BUFFER_SIZE && _inputBuffer.find("\r\n") == std::string::npos)
	{
		_inputBuffer.clear();
		return false;
	}
	return true;
}

std::string	Client::getFullMessage()
{
	size_t pos = _inputBuffer.find("\r\n");
	if(pos != std::string::npos)
	{
		std::string _fullMsg;
		_fullMsg = _inputBuffer.substr(0, pos);
		_inputBuffer = _inputBuffer.substr(pos + 2);
		return _fullMsg;
	}
	return std::string("");
}

bool	Client::operator==(const Client &other) const
{
	return _socketFd == other._socketFd;
}





 #include <string.h>
 #include <errno.h>

// the last argument specifies the flags that control the behavior of the send operation. 
// When set to 0, it means that no special flags are being used, and the send operation should proceed with default behavior.
void Client::sendMessage(const std::string &ircMessage) const
{
	if (ircMessage.empty())
		return ;
	std::string msg = ircMessage;
	if(msg[msg.size() - 1] != '\n')
		msg += "\n";
	ssize_t bytesSent = send(_socketFd, msg.c_str(), msg.length(), 0);
	Logger::log("Message send:\n\tMSG -->\t\t" 		+ msg);
	if (bytesSent == -1)
		Logger::log("\t ERROR -->\n\t" + std::string(strerror(errno)));
}

void	Client::sendMessage(const std::string &code, const std::string &message) const
{
	std::string ircMessage = 
		":localhost " + code + " " + _nickname + " " + message + "\n";
	sendMessage(ircMessage);
}


void Client::joinChannel(Channel *channel)
{
		_channels.push_back(channel);
		//  Now talking on #newwww
		//  astein (alex@F456A.75198A.60D2B2.ADA236.IP) has joined
		// info() TODO:
}

void Client::leaveChannel(Channel *channel)
{
		_channels.remove(channel);
}

void Client::getInvited(Channel *channel)
{
		_invitations.push_back(channel);
}

void Client::getKicked(Channel *channel)
{
		for (std::list<Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		{
				//TODO: find a channel if user's channels and delete it from list
		}
		(void)channel;  
		//TODO: send the message to the client that ha was kicked. also send it to the channel
}

void    Client::setUniqueName(const std::string &nickname)
{
	_nickname = nickname;
}

void Client::setUsername(const std::string &username)
{
	info("Set username " + username, CLR_GRN);
	_username = username;
}

void Client::setFullname(const std::string &fullname)
{
		_fullname = fullname;
}

void Client::setHostname(const std::string &hostname)
{
		_hostname = hostname;
}

int Client::getSocketFd() const
{
	return _socketFd;
}

const std::string &Client::getUniqueName() const
{
		return _nickname;
}

const std::string &Client::getUsername() const
{
		return _username;
}

const std::string &Client::getFullname() const
{
		return _fullname;
}

const std::string &Client::getHostname() const
{
		return _hostname;
}

// Static Function


// void	Client::reserveNickName(const std::string &nickname) throw(NickNameException)
// {
// 	info ("Reserving Nickname: ", CLR_BLU);
// 	info ("\t->Nickname:\t" 	+ nickname, CLR_BLU);
// 	if (Client::_nicknames.find(nickname) != Client::_nicknames.end())
// 	{
// 		throw NickNameException("Nickname in use!"); // '" + nickname + "' already in use");
// 	}
// 	Client::_nicknames.insert(nickname);
// }

// EXCEPTION
NickNameException::NickNameException(const std::string &message) : _message(message)
{
	// Nothing to do here
}

NickNameException::~NickNameException() throw()
{
	// Nothing to do here
}

const char *NickNameException::what() const throw()
{
	return _message.c_str();
}