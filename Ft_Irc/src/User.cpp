#include "../include/Server.hpp"

User::User(const int& fd) : status(0), fd(fd)
{
	
}

User::~User(){}

User::User(const User& source)
{
	(void)source;
}

User& User::operator=(const User& source)
{
	(void)source;
	return (*this);
}

void User::setUserName(const std::string& item)
{
	userName = item;
}

void User::setRealName(const std::string& item)
{
	realName = item;
}

void	User::setNickName(const std::string &item)
{
	nickName = item;
}

const int&	User::getStatus() const
{
	return status;
}

int& User::setStatus()
{
	return status;
}

const std::string&	User::getNickName() const
{
	return nickName;
}

const std::string& User::getUserName() const
{
	return userName;
}

const std::string& User::getRealName() const
{
	return realName;
}

bool User::isLogin()
{
	return status == ISLOGIN;
}

const int& User::getFd() const
{
	return fd;
}

void User::send(const std::string& message)
{
	reply(getFd(), message);
}
