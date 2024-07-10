#pragma once
#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <exception>
#include <cstdio>
#include <cstring>
#include <csignal>
#include <climits>

#define BUFFER 1024 + 1

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

/*
c++ irc 서버에서 사용중인 것과
동일한 class 선언과 include 방식을 사용하였음
*/
#define Core __attribute__ ((visibility ("default")))

class Command;
class Channel;
class ChannelManager;
class User;
class UserManager;
class Server;
class IErrorMessage;
class KickErrorMessages;
class NumericReplies;

/*
전역변수처럼 접근할 수 있음
*/
Core extern Server* serverInstance;

#include "Utils.hpp"
#include "Channel.hpp"
#include "ChannelManager.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include "Command.hpp"
#include "NumericReplies.hpp"
#include "IRCMessage.hpp"

class Core Server
{
	public:
		Server(const unsigned& port, const std::string& pass); // main() arugments
		~Server(); // 미구현
		void run(); //무한 루프
		void init(); // init 잘못 되면 std::exit
		void destroy();

		Command commandManager;
		UserManager userManager; //유저 리스트 관리자
		ChannelManager channelManager;

		fd_set masterSet; // fd_set 파일 select에서 사용
		int	maxFd; // max fd. select에서 사용
		void setDoWhile(const int &n);
		const std::string& getPassword() const;
		const std::string& getServerName() const;
	private:
		char buf[BUFFER]; // recv 받기용 buffer
		
		int sockFd; // 서버 소켓
		int doWhile;
		const std::string name;
		const std::string password;
		const unsigned int port;
        Server(const Server &copy);
		Server();
		bool initSockFd(); // socket init하기
		Server& operator=(const Server &assign);
};

#endif
