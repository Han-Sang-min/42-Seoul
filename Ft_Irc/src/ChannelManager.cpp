#include "../include/Server.hpp"

ChannelManager* channelInstance = NULL;

// Constructors
ChannelManager::ChannelManager()
{
	channelInstance = this;
	//std::cout << "\e[0;33mDefault Constructor called of ChannelManager\e[0m" << std::endl;
}

ChannelManager::ChannelManager(const ChannelManager &copy)
{
	(void) copy;
	//std::cout << "\e[0;33mCopy Constructor called of ChannelManager\e[0m" << std::endl;
}

ChannelManager::~ChannelManager()
{
	//std::cout << "\e[0;31mDestructor called of ChannelManager\e[0m" << std::endl;
}

ChannelManager & ChannelManager::operator=(const ChannelManager &assign)
{
	(void) assign;
	return *this;
}

Channel * ChannelManager::find(const std::string& channel) const
{
	return channelList.find(channel) != channelList.end() ? channelList.find(channel)->second : NULL;
}

bool ChannelManager::isValidChannel(const std::string& channel)
{
	if(*(channel.rend() - 1) != '#')
		return false;

	std::string::const_iterator it = channel.begin();
	for(; it != channel.end(); ++it)
	{
		switch(*it)
		{
			case ' ' :
			case '\7':
			case ',' :
				return false;
		}
	}
	return true;
}
