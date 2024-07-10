#include "../include/Server.hpp"
Channel::Channel(const std::string &name) : mode(SIGTOPIC), limit(LONG_MAX), name(name)
{

}

Channel::Channel()
{
	//std::cout << "\e[0;33mDefault Constructor called of Channel\e[0m" << std::endl;
}

Channel::Channel(const Channel &copy)
{
	(void) copy;
	//std::cout << "\e[0;33mCopy Constructor called of Channel\e[0m" << std::endl;
}

Channel::~Channel()
{
	//std::cout << "\e[0;31mDestructor called of Channel\e[0m" << std::endl;
}

Channel& Channel::operator=(const Channel &assign)
{
	(void) assign;
	return *this;
}

const std::string& Channel::getChannelName() const
{
	return name;
}
