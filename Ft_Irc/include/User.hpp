#pragma once
#ifndef USER_HPP
# define USER_HPP
# define NICKSIG 1
# define USERSIG 2
# define PASSSIG 4
# define ISLOGIN 7

typedef std::set<std::string> usedChannelMap;
typedef std::map<User *, std::set<Channel *> > adjacentMap;

class Core User
{
	private:
		int			status;
		int			fd;
		std::string nickName;
		std::string userName;
		std::string realName;
		User(const User& source);
		User& operator=(const User& source);
		 
	public:
		std::string data;
		User(const int& fd);
		~User();
		const int& getFd() const;
		const int& getStatus() const;
		const std::string& getUserName() const;
		const std::string& getRealName() const;
		const std::string& getNickName() const;
		int& setStatus();
		void setUserName(const std::string& item);
		void setRealName(const std::string& item);
		void setNickName(const std::string& item);
		bool isLogin();
		usedChannelMap	usedChannelList;
		adjacentMap		adjacentList;
		void send(const std::string& message);
};
#endif
