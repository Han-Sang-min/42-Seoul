#include "../include/Server.hpp"

//맨 왼쪽부터 오른쪽까지 space 제거. 맨 오른쪽에서 왼쪽까지 space 제거 
void trim(std::string& s, const std::string& t)
{
    s.erase(0, s.find_first_not_of(t));
    s.erase(s.find_last_not_of(t) + 1);
}

//중간에 있는 space 1개로 줄임
void mergeSpace(std::string& s)
{
    std::size_t doubleSpace = s.find("  ");
    while(doubleSpace != std::string::npos)
    {
        s.erase(doubleSpace, 1);
        doubleSpace = s.find("  ");
    }
}
//delim 기준으로 나눔
void tokenize(std::string &str, char const &delim,
            std::vector<std::string> &out)
{
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim))
    {
        out.push_back(s);
    }
}

void reply(const int& fd, const std::string& s)
{
	if(FD_ISSET(fd, &serverInstance->masterSet))
	{
		if(send(fd, s.c_str(), s.length(), MSG_NOSIGNAL) == -1)
		{
			if(errno == EPIPE || errno == EACCES)
			{
				return ;
			}
			if(errno == ENOMEM)
			{
				throw std::runtime_error("Memory");
			}
			std::perror("send");
		}
	}
}
