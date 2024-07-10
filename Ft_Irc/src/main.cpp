#include "../include/Server.hpp"
#include <stdexcept>

bool isNumber(const char *s)
{
    while(*s)
    {
        if(*s < '0' || *s > '9') return false;
        ++s;
    }
    return true;
}

bool isValidPassword(const char *s)
{
    return isNumber(s);
}

void isValidArg(const int& ac, char **argv)
{
    if(ac != 3) throw std::runtime_error("Not enough parameter");
    if(!isNumber(argv[1]) || !isValidPassword(argv[2])) throw std::runtime_error("Invalid argument");
    long port = std::strtol(argv[1], NULL, 10);
	long password = std::strtol(argv[2], NULL, 10);
    if(errno == ERANGE || port < 1024L || port > 65535L || password < 0L || password >= 10000L) throw std::runtime_error("Invalid argument");
}

void func()
{
	system("leaks ircserv");
	if(close(0) == -1) std::exit(EXIT_FAILURE);
	if(close(1) == -1) std::exit(EXIT_FAILURE);
	if(close(2) == -1) std::exit(EXIT_FAILURE);
}

void sigHandler(int sig)
{
	(void)sig;
	if(serverInstance)
	{
		serverInstance->setDoWhile(0);
		return ;
	}
	else
	{
		std::exit(EXIT_SUCCESS);
	}
}

int main(int ac, char *argv[])
{
	try
	{
		errno = 0;
		std::srand(time(NULL));
		if(errno == EFAULT) return (EXIT_FAILURE);
		std::signal(SIGINT, sigHandler);
    	std::signal(SIGQUIT, SIG_IGN);
    	std::signal(SIGTSTP, SIG_IGN);
		if(!MSG_NOSIGNAL)
		{
			std::signal(SIGPIPE, SIG_IGN);
		}
		#ifdef DEBUG
		{
			std::cout << "atexit is started." << std::endl;
			if(std::atexit(func) != 0) throw std::exception();
		}
		#endif
		isValidArg(ac, argv);
		Server server(static_cast<uint16_t>(std::strtol(argv[1], NULL, 10)), argv[2]);
		server.init();
		server.run();
	}
	catch(std::exception const &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	#ifndef DEBUG
	if(close(0) == -1) std::exit(EXIT_FAILURE);
	if(close(1) == -1) std::exit(EXIT_FAILURE);
	if(close(2) == -1) std::exit(EXIT_FAILURE);
	#endif
	return (EXIT_SUCCESS);
}
