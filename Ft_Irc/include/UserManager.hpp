#pragma once
#ifndef USERMANAGER_HPP
# define USERMANAGER_HPP

typedef std::map<std::string, User *> userMapByNick;
typedef std::map<int, User *> userMapByFd;
typedef std::set<std::string> usedNickSet;

class Core UserManager
{
	public:
		UserManager();
		~UserManager();

		void addUser(const int& socket); // 유저 추가
		void delUser(User* user);
		User* findNick(const std::string& nick);
		User* findFd(const int& fd); // fd로 유저 찾기
		userMapByNick userListByNick;
		userMapByFd userListByFd;
		usedNickSet usedNickList;
		ChannelManager *channelManager;
		static bool defaultIsNick(const std::string& n);
	private:
		UserManager(const UserManager& copy);
		UserManager & operator=(const UserManager& assign);
};

#endif
