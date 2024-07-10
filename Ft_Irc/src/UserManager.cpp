#include "../include/Server.hpp"

// Constructors
UserManager::UserManager()
{
	//std::cout << "\e[0;33mDefault Constructor called of UserManager\e[0m" << std::endl;
}

UserManager::UserManager(const UserManager &copy)
{
	(void) copy;
	//std::cout << "\e[0;33mCopy Constructor called of UserManager\e[0m" << std::endl;
}


// Destructor
UserManager::~UserManager()
{
	//std::cout << "\e[0;31mDestructor called of UserManager\e[0m" << std::endl;
}

// Operators
UserManager & UserManager::operator=(const UserManager &assign)
{
	(void) assign;
	return *this;
}

void UserManager::addUser(const int& socket)
{
	userListByFd[socket] = new User(socket);
}

void UserManager::delUser(User* user)
{
	std::map<User *, std::set<Channel *> >::iterator it2 = user->adjacentList.begin();
	for(; it2 != user->adjacentList.end(); ++it2)
	{
		(*it2).first->adjacentList.erase(user);
	}

	std::set<std::string>::iterator it = user->usedChannelList.begin();
	for(; it != user->usedChannelList.end();++it)
	{
		channelManager->channelList[*it]->memberList.erase(user);
		channelManager->channelList[*it]->operList.erase(user);
		channelManager->channelList[*it]->inviteList.erase(user);
		if(channelManager->channelList[*it]->memberList.begin() == channelManager->channelList[*it]->memberList.end())
		{
			delete channelManager->channelList[*it];
			channelManager->channelList.erase(*it);
		}
	}

	serverInstance->commandManager.commandList.erase(user->getFd());

	if(close(user->getFd()) == -1) throw std::runtime_error("User fd");
	FD_CLR(user->getFd(), &serverInstance->masterSet);
	if(user->getFd() == serverInstance->maxFd) --serverInstance->maxFd;
	usedNickList.erase(user->getNickName());
	userListByNick.erase(user->getNickName());
	userListByFd.erase(user->getFd());
	delete user;
}

User* UserManager::findNick(const std::string& nick)
{
	return userListByNick.find(nick) != userListByNick.end() ? userListByNick.find(nick)->second : NULL;
}

User* UserManager::findFd(const int& fd)
{
	return userListByFd.find(fd) != userListByFd.end() ? userListByFd.find(fd)->second : NULL;
}

bool UserManager::defaultIsNick(const std::string& n)
{
	for (std::string::const_iterator i = n.begin(); i != n.end(); ++i)
	{
		if ((*i >= 'A') && (*i <= '}'))
		{
			continue;
		}

		if ((((*i >= '0') && (*i <= '9')) || (*i == '-')) && (i != n.begin()))
		{
			continue;
		}
		return false;
	}
	return true;
}
