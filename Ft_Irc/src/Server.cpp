#include "../include/Server.hpp"

Server* serverInstance = NULL;

Server::Server(const unsigned& port, const std::string& pass) : doWhile(42), name("ircserv"), password(pass), port(port)
{
	serverInstance = this;
	channelManager.userManager = &userManager;
	userManager.channelManager = &channelManager;
	commandManager.userManager = &userManager;
	commandManager.channelManager = &channelManager;
}
Server::Server(const Server& copy) : name(""), password(""), port(0)
{
	(void) copy;
}
Server::~Server()
{
	destroy();
	serverInstance = NULL;
}
Server::Server() : name(""), password(""), port(0)
{
	
}
Server & Server::operator=(const Server& assign)
{
	(void) assign;
	return *this;
}

bool Server::initSockFd()
{
	struct sockaddr_in myAddr;
	int yes = 1;
	if (fcntl(0, F_SETFL, O_NONBLOCK) < 0)
	{
		std::perror("fcntl");
		return false;
	} //non blocking 설정하기
	if (fcntl(1, F_SETFL, O_NONBLOCK) < 0)
	{
		std::perror("fcntl");
		return false;
	} //non blocking 설정하기
	if (fcntl(2, F_SETFL, O_NONBLOCK) < 0)
	{
		std::perror("fcntl");
		return false;
	} //non blocking 설정하기
	if((sockFd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::perror("socket");
		return false;
	} // tcp ipv4으로 소켓 설정하기
	if (fcntl(sockFd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::perror("fcntl");
		return false;
	} //non blocking 설정하기
	myAddr.sin_family = AF_INET; // inv4
	myAddr.sin_port = htons(port); // host to netowrk short
	myAddr.sin_addr.s_addr = INADDR_ANY; //choose as random

	if(setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) < 0)
	{
		std::perror("setsockopt");
		return false;
	} // bind 하기전 사용
	if(bind(sockFd, (struct sockaddr *)&myAddr, sizeof myAddr) < 0)
	{
		std::perror("bind");
		return false;
	} // 소켓과 port 넘버 합치기
	if(listen(sockFd, 20) < 0)
	{
		std::perror("listen");
		return false;
	} // 연결 듣기. 20개는 최대 연결 대기 큐 

	maxFd = sockFd;
	FD_ZERO(&masterSet);
	FD_SET(sockFd, &masterSet); //init하기
	return true;
}

void Server::destroy()
{
	for(int i = sockFd; i <= maxFd; ++i)
	{
		close(i);
	}
	std::map<int, User *>::iterator it =userManager.userListByFd.begin();
	for(; it != userManager.userListByFd.end(); ++it)
	{
		delete (*it).second;
	}
	std::map<std::string, Channel *>::iterator it2 = channelManager.channelList.begin();
	for(; it2 != channelManager.channelList.end(); ++it2)
	{
		delete (*it2).second;
	}
}

void Server::init()
{
	if (initSockFd() == false) throw std::runtime_error("Init");
}

void Server::run()
{
	timeval tVal;
	struct      sockaddr_storage remoteAddr;
	socklen_t   addrLen;

	tVal.tv_sec = 1;
	tVal.tv_usec = 0; // 최대 1초까지 체크

	fd_set rFdSet, wFdSet, errFdSet;
	int hasRead, hasWrite, hasError, newFd, nBytes, result, i, j;
	std::set<int>::const_iterator it2;
	while(doWhile)
	{
		rFdSet = wFdSet = errFdSet = masterSet;
		result = select(maxFd + 1, &rFdSet, &wFdSet, &errFdSet, &tVal);
		if(result < 0)
		{
			throw std::runtime_error("select");
		}
		for(i = 0, j = result; i <= maxFd && j > 0; ++i)
		{
			hasRead = FD_ISSET(i, &rFdSet), hasWrite = FD_ISSET(i, &wFdSet), hasError = FD_ISSET(i, &errFdSet);
			if(!(hasRead || hasWrite || hasError)) continue; // 변화없을시
			--j;
			if(hasError) //넘어가기
			{
				continue;
			}
			if(hasRead)
			{
				if(i == sockFd) // 유저추가
				{
					addrLen = sizeof remoteAddr;
					newFd = accept(sockFd, (struct sockaddr *)&remoteAddr, &addrLen);
					if(newFd < 0)
					{
						if(errno == EAGAIN || errno == EWOULDBLOCK) continue; // non block일시 필요
						throw std::runtime_error("accept");
					}
					if(newFd >= FD_SETSIZE)
					{
						reply(newFd, "ERROR :Closing link: [Quit: leaving]\r\n");
						if (close(newFd) == -1) throw std::runtime_error("Closing link");
						continue;
					}
					if (fcntl(newFd, F_SETFL, O_NONBLOCK) < 0)
					{
						std::perror("fcntl");
						throw std::runtime_error("fcntl");
					} //non blocking 설정하기
					FD_SET(newFd, &masterSet);
					if(newFd > maxFd) maxFd = newFd;
					//add with dump item to usersList
					std::cout << "server: new connection from " + str(newFd) << std::endl;
					userManager.addUser(newFd);
				}
				else //데이터 받기
				{
					if((nBytes = recv(i, buf, sizeof buf - 1, 0)) <= 0) // 에러 발생시 유저 삭제
					{
						if(errno == EWOULDBLOCK || errno == EAGAIN )
						{
							continue;
						}
						if(nBytes == 0) std::cout << "socket " + str(i) + " closed" << std::endl;
						else std::perror("recv");
						
						userManager.delUser(userManager.findFd(i));
					}
					else
					{
						User *user = userManager.findFd(i);
						buf[nBytes] = '\0';
						if(std::memchr(buf, '\n', nBytes))
							commandManager.commandList.insert(i);
						user->data += buf;
						if(user->data.length() > 4096)
						{
							NumericReplies numbericReplies(user);
							numbericReplies.closingLinkBufferExceeded();
							userManager.delUser(user);
							commandManager.commandList.erase(i);
						}
					}
				}
			}
			if(commandManager.commandList.find(i) != commandManager.commandList.end() && hasWrite)
			{
				it2 = commandManager.commandList.begin();
				User *user = userManager.findFd(*it2);
				std::string s;
				std::stringstream ss;
				user->data.erase(remove(user->data.begin(), user->data.end(), '\r'), user->data.end());
				if(*(user->data.rbegin()) != '\n')
				{
					s = user->data.find_last_of('\n') + 1;
					ss << user->data;
					user->data = s;
				}
				else
				{
					ss << user->data;
					user->data.clear();
				}
				while(std::getline(ss, s, '\n'))
				{
					User* user2 = userManager.findFd(*it2);
					if(user2 == NULL) break;
					if(s.length() == 0 || s.find_first_not_of(' ') == std::string::npos)
					{
						continue;
					}
					trim(s, " ");
					mergeSpace(s);
					std::vector<std::string> cmdList;
					tokenize(s, ' ', cmdList);

					/*execute*/
					std::map<std::string, void (Command::*)(const std::vector<std::string> &, User *)>::const_iterator it;
					std::transform((cmdList.front()).begin(), (cmdList.front()).end(), (cmdList.front()).begin(), ::toupper);
					it = commandManager.getCommandSwitch().find(cmdList.front());
					if(it != commandManager.getCommandSwitch().end())
					{
						(commandManager.*it->second)(cmdList, user2);
					}
					else
					{
						if(user2->isLogin())
						{
							NumericReplies numericReplies(user2);
							numericReplies.unknownCommand(cmdList.front());
						}
					}
				}
				commandManager.commandList.clear();
			}
		}
	}
}
void Server::setDoWhile(const int &n)
{
	doWhile = n;
}

const std::string& Server::getPassword() const
{
	return password;
}

const std::string& Server::getServerName() const
{
	return name;
}
