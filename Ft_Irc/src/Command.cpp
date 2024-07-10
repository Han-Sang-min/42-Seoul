#include "../include/Server.hpp"

Command::Command()
{
	commandSwitch["PASS"] = &Command::pass;
	commandSwitch["NICK"] = &Command::nick;
	commandSwitch["USER"] = &Command::user;
	commandSwitch["JOIN"] = &Command::join;
	commandSwitch["PING"] = &Command::ping;
	commandSwitch["QUIT"] = &Command::quit;
	commandSwitch["PRIVMSG"] = &Command::privmsg;
	commandSwitch["INFO"] = &Command::info;
	commandSwitch["KICK"] = &Command::kick;
	commandSwitch["PART"] = &Command::part;
	commandSwitch["INVITE"] = &Command::invite;
	commandSwitch["TOPIC"] = &Command::topic;
	commandSwitch["MODE"] = &Command::mode;
}
Command::~Command() {}
Command::Command(Command const& obj){(void)obj;}
Command& Command::operator= (const Command& obj){(void)obj;return *this;}

const std::map<std::string, void(Command::*)(const std::vector<std::string> &, User *)>& Command::getCommandSwitch() const
{
	return commandSwitch;
}

void Command::pass(const std::vector<std::string> &command, User *user)
{
	NumericReplies numbericReplies(user);

	if(command.size() < 2)
	{
		numbericReplies.needMoreParams(command.front());
		return ;
	}
	if(user->isLogin())
	{
		numbericReplies.PasswdMisMatch();
		return ;
	}
	if(user->getStatus() & PASSSIG)
	{
		return ;
	}
	std::vector<std::string>::const_iterator it = command.begin() + 1;
	if(*it == serverInstance->getPassword())
	{
		user->setStatus() |= PASSSIG;
	}
}

void Command::nick(const std::vector<std::string> &command, User *user) {
	NumericReplies numbericReplies(user);

	if(command.size() < 2)
	{
		numbericReplies.needMoreParams(command.front());
		return ;
	}
	std::vector<std::string>::const_iterator it2;
	it2 = command.begin() + 1;
	std::string newNick = (*it2).length() > 24 ? (*it2).substr(0, 24) : *it2;
	if(user->getNickName() == newNick) return ;
	if(!UserManager::defaultIsNick(newNick))
	{
		numbericReplies.erroneusNickname(newNick);
		return ;
	}
	if(userManager->usedNickList.find(newNick) != userManager->usedNickList.end())
	{
		numbericReplies.NicknameIsAlreadInUse(newNick);
		return ;
	}
	if(user->isLogin())
	{
		reply(user->getFd(), ":" + user->getNickName()  + "!" + user->getUserName() +"@127.0.0.1 " + command.front() + " :"+ newNick + "\r\n");
		std::map<User *, std::set<Channel *> >::const_iterator it3 = user->adjacentList.begin();
		for(; it3 != user->adjacentList.end(); ++it3)
		{
			reply((*it3).first->getFd(), ":" + user->getNickName()  + "!" + user->getUserName() +"@127.0.0.1 " + command.front() + " :"+ newNick + "\r\n");
		}
	}
	userManager->userListByNick.erase(user->getNickName());
	userManager->usedNickList.erase(user->getNickName());
	user->setNickName(newNick);
	userManager->usedNickList.insert(newNick);
	userManager->userListByNick[user->getNickName()] = user;
	if(user->getStatus() & NICKSIG)
	{
		return ;
	}
	user->setStatus() |= NICKSIG;
	if((user->getStatus() ^ PASSSIG) == ISLOGIN)
	{
		reply(user->getFd(), "ERROR :Closing link: (" + user->getUserName() + "@127.0.0.1) [Access denied by configuration]\r\n");
		std::cout << "socket " + str(user->getFd()) + " closed" << std::endl;
		userManager->delUser(user);
		return ;
	}
	else if(user->getStatus() == ISLOGIN)
	{
		firstMessage(user);
	}
}

void Command::user(const std::vector<std::string> &command, User *user)
{
	NumericReplies numbericReplies(user);

	if(command.size() < 5)
	{
		numbericReplies.needMoreParams(command.front());
		return ;
	}
	if(user->isLogin())
	{
		numbericReplies.PasswdMisMatch();
		return ;
	}
	std::vector<std::string>::const_iterator it = command.begin() + 1;
	if((*it).length() > 24)
		user->setUserName((*it).substr(0, 24));
	else
		user->setUserName(*it);
	it += 3;
	if((*it).length() > 24)
		user->setRealName((*it).substr(0, 24));
	else
		user->setRealName(*it);
	if(user->getStatus() & USERSIG)
	{
		return ;
	}
	user->setStatus() |= USERSIG;
	if((user->getStatus() ^ PASSSIG) == ISLOGIN)
	{
		reply(user->getFd(), "ERROR :Closing link: (" + user->getUserName() + "@127.0.0.1) [Access denied by configuration]\r\n");
		std::cout << "socket " + str(user->getFd()) + " closed" << std::endl;
		userManager->delUser(user);
		return ;
	}
	if(user->getStatus() == ISLOGIN)
	{
		firstMessage(user);
	}
}

void Command::join(const std::vector<std::string> &command, User *user)
{
	NumericReplies numbericReplies(user);
	if(command.size() < 2)
	{
		numbericReplies.needMoreParams(command.front());
		return ;
	}
	if(!user->isLogin())
	{
		numbericReplies.NotRegistered();
		return ;
	}
	if(user->usedChannelList.size() > 1024)
	{
		numbericReplies.tooManyChannels(command.front());
		return ;
	}
	std::vector<std::string>::const_iterator it = command.begin() + 1;
	if(!ChannelManager::isValidChannel(*it))
	{
		numbericReplies.badChanMask(*it);
		return ;
	}

	std::string name = (*it).substr(1);
	if(name.length() > 42)
	{
		name = name.substr(0, 42);
	}
	Channel *result = channelManager->find(name);
	if(result)
	{
		if(channelManager->channelList[name]->memberList.find(user) != channelManager->channelList[name]->memberList.end())
		{
			return ;
		}
		if(channelManager->channelList[name]->inviteList.find(user) == channelManager->channelList[name]->inviteList.end())
		{
			if(channelManager->channelList[name]->mode & SIGINVITE)
			{
				reply(user->getFd(), ":ircserv 473 " + user->getNickName() + " " + *it + " :Cannot join channel (invite only)\r\n");
				return ;
			}
			if((channelManager->channelList[name]->mode & SIGLIMIT) && channelManager->channelList[name]->memberList.size() >= channelManager->channelList[name]->limit)
			{
				reply(user->getFd(), ":ircserv 471 " + user->getNickName() + " " + *it + " :Cannot join channel (channel is full)\r\n");
				return;
			}
			if((channelManager->channelList[name]->mode & SIGKEY) && (it + 1 == command.end() || *(it + 1) != channelManager->channelList[name]->key))
			{
				reply(user->getFd(), ":ircserv 475 " + user->getNickName() + " " + *it + " :Cannot join channel (incorrect channel key)\r\n");
				return ;
			}
		}
		else
		{
			channelManager->channelList[name]->inviteList.erase(user);
		}
		channelManager->channelList[name]->memberList.insert(user);
		user->usedChannelList.insert(name);
	}
	else
	{
		channelManager->channelList[name] = new Channel(name);
		channelManager->channelList[name]->memberList.insert(user);
		channelManager->channelList[name]->operList.insert(user);
		user->usedChannelList.insert(name);
		std::string s = ":" + user->getNickName() + "!" + user->getUserName() + "@127.0.0.1 " + command.front() + " :" + *it +"\r\n";
		s += ":ircserv 353 " + user->getNickName() + " = " + *it + " :" + "@" + user->getNickName() + "\r\n";
		reply(user->getFd(), s);
		reply(user->getFd(), ":42!42@127.0.0.1 NOTICE " + *it + " " + "weclome to join " +  name + " channel" + "\r\n");
		return ;
	}

	std::set<User *>::iterator it3;
	std::string s;
	s = ":" + user->getNickName() + "!" + user->getUserName() + "@127.0.0.1 " + command.front() + " :" + *it +"\r\n";
	it3 = channelManager->channelList[name]->memberList.begin();
	for(; it3 != channelManager->channelList[name]->memberList.end(); ++it3)
	{
		if(*it3 != user)
		{
			user->adjacentList[*it3].insert(channelManager->channelList[name]);
			(*it3)->adjacentList[user].insert(channelManager->channelList[name]);
		}
		else
		{
			if(!channelManager->channelList[name]->topic.empty())
			{
				s += ":ircserv 332 "+ user->getNickName() + " " + *it + " :" + channelManager->channelList[name]->topic + "\r\n";
				s += ":ircserv 333 " + user->getNickName() + " " + *it + " " + user->getUserName() + "!root@127.0.0.1 :" + str(channelManager->channelList[name]->topicTime) + "\r\n";
			}
			s += ":ircserv 353 " + user->getNickName() + " = " + *it + " :";
			std::set<User *>::iterator it4;
			it4 = channelManager->channelList[name]->memberList.begin();
			while(it4 != channelManager->channelList[name]->memberList.end())
			{
				if(channelManager->channelList[name]->operList.find(*it4) != channelManager->channelList[name]->operList.end())
				{
					s += "@";
				}
				s += (*it4)->getNickName();
				++it4;
				if(it4 != channelManager->channelList[name]->memberList.end())
				{
					s += " ";
				}
			}
			s += "\r\n";
		}
		reply((*it3)->getFd(), s);
	}
	reply(user->getFd(), ":42!42@127.0.0.1 NOTICE " + *it + " " + "weclome to join " +  name + " channel" + "\r\n");
}

void Command::privmsg(const std::vector<std::string> &command, User *user)
{
	NumericReplies numbericReplies(user);
	if(command.size() < 3)
	{
		numbericReplies.needMoreParams(command.front());
		return ;
	}
	if(!user->isLogin())
	{
		numbericReplies.NotRegistered();
		return ;
	}

	std::vector<std::string>::const_iterator it = command.begin() + 1;
	if(*((*it).rend() - 1) == '#')
	{
		std::string name = (*it).substr(1);
		Channel *channel = channelManager->find(name);
		if(channel)
		{
			if(channel->memberList.find(user) == channel->memberList.end())
			{
				 numbericReplies.notOnChannel(*it);
				 return;
			}
			IRCMessage IRCMessage;
			IRCMessage.privmsgHandler(user, channel, *(command.begin()), command);
		}
		else
		{
			numbericReplies.noSuchChannel(*it);
		}
	}
	else
	{
		if(*it == user->getNickName())
		{
			return ;
		}
		User *target = userManager->findNick(*it);
		if(target)
		{
			IRCMessage IRCMessage;
			IRCMessage.privmsgHandler(user, target, *(command.begin()), command);
		}
		else
		{
			numbericReplies.noSuchNick(*it);
		}
	}
}

void Command::ping(const std::vector<std::string> &command, User *user)
{
	NumericReplies numbericReplies(user);
	if(command.size() < 2)
	{
		numbericReplies.needMoreParams(command.front());
		return ;
	}
	if(!user->isLogin())
	{
		numbericReplies.NotRegistered();
		return ;
	}
	{
		IRCMessage IRCMessage;
		IRCMessage.pongMessage(user);
	}
}

void Command::quit(const std::vector<std::string> &command, User *user)
{
	(void)command;
	std::cout << "socket " + str(user->getFd()) + " closed" << std::endl;
	reply(user->getFd(), "ERROR :Closing link: (" + user->getUserName() + "@127.0.0.1) [Quit: leaving]\r\n");
	std::map<User *, std::set<Channel *> >::const_iterator it = user->adjacentList.begin();
	for(; it != user->adjacentList.end(); ++it)
	{
		reply((*it).first->getFd(), ":" + user->getNickName() + "!" + user->getUserName() + "@127.0.0.1 QUIT :Quit: leaving\r\n");
	}
	userManager->delUser(user);
}

void Command::info(const std::vector<std::string> &command, User *user)
{
	(void)command;
	static const char *table[] = 
	{
		"\"Wisdom is not a product of schooling but of the lifelong attempt to acquire it.\" Albert Einstein",
		"\"Lessons in life will be repeated until they are learned.\" - Frank Sonnenberg",
		"\"Wise men talk because they have something to say; Fools, because they have to say something.\" - Plato",
		"Knowledge is knowing what to say. Wisdom is knowing when to say it.\" - Anonymous",
		"\"Wisdom is the daughter of experience.\" - Anonymous",
		"\"Knowledge speaks, but wisdom listens.\" - Jimi Hendrix",
		"\"Turn your wounds into wisdom.\" - Oprah Winfrey",
		"\"The man who asks a question is a fool for a minute, the man who does not ask is a fool for life.\" - Confucius",
		"\"Knowledge is learning something every day. Wisdom is letting go of something every day.\" - Zen Proverb",
		"\"Never mistake knowledge for wisdom. One helps you make a living; the other helps you make a life.\" - Sandra Carey",
		"\"A loving heart is the truest wisdom.\" - Charles Dickens"
	};
	int n = std::rand() % 11;
	reply(user->getFd(), str(table[n]) + "\r\n");
}

void Command::kick(const std::vector<std::string> &command, User *user)
{
	NumericReplies numbericReplies(user);
	if(command.size() < 3)
	{
		numbericReplies.needMoreParams(command.front());
		return ;
	}
	if(!user->isLogin())
	{
		numbericReplies.NotRegistered();
		return ;
	}

	std::vector<std::string>::const_iterator it = command.begin() + 1;
	std::string name = (*it).substr(1);
	Channel* ch = channelManager->find(name);
	if(!ch || *((*it).begin()) != '#')
	{
		numbericReplies.noSuchChannel(*it);
		return;
	}
	std::string victimName = *(it + 1);
	User* victim = userManager->findNick(victimName);
	if(!victim)
	{
		numbericReplies.noSuchNick(victimName);
		return ;
	}
	if(channelManager->channelList[name]->operList.find(user) == channelManager->channelList[name]->operList.end())
	{
		numbericReplies.chanOpPrivsNeeded(*it);
		return ;
	}

	std::set<User *>::const_iterator it3;
	it3 = channelManager->channelList[name]->memberList.begin();
	std::string s;
	s = ":" + user->getNickName() + "!" + user->getUserName() + 
		"@127.0.0.1 " + command.front() + " " + *it + " " + victimName + " :" +"\r\n";
	for(; it3 != channelManager->channelList[name]->memberList.end(); ++it3)
	{
		reply((*it3)->getFd(), s);
		user->adjacentList[*it3].erase(channelManager->channelList[name]);
		if(user->adjacentList[*it3].empty())
		{
			user->adjacentList.erase(*it3);
		}
		(*it3)->adjacentList[user].erase(channelManager->channelList[name]);
		if((*it3)->adjacentList[user].empty())
		{
			(*it3)->adjacentList.erase(user);
		}
	}
	channelManager->channelList[name]->memberList.erase(victim);
	channelManager->channelList[name]->operList.erase(victim);
	channelManager->channelList[name]->inviteList.erase(victim);
	if(channelManager->channelList[name]->memberList.begin() == channelManager->channelList[name]->memberList.end())
	{
		delete channelManager->channelList[name];
		channelManager->channelList.erase(name);
	}
	victim->usedChannelList.erase(name);
}

void Command::part(const std::vector<std::string> &command, User *user)
{
	NumericReplies numbericReplies(user);
	if(command.size() < 2)
	{
		numbericReplies.needMoreParams(command.front());
		return ;
	}
	if(!user->isLogin())
	{
		numbericReplies.NotRegistered();
		return ;
	}
	std::vector<std::string>::const_iterator it = command.begin() + 1;
	std::string name = (*it).substr(1);
	Channel* ch = channelManager->find(name);
	if(!ch || *((*it).begin()) != '#')
	{
		numbericReplies.noSuchChannel(*it);
		return;
	}
	if(channelManager->channelList[name]->memberList.find(user) == channelManager->channelList[name]->memberList.end())
	{
		numbericReplies.notOnChannel(*it);
		return ;
	}

	std::set<User *>::const_iterator it3;
	std::string s;
	it3 = channelManager->channelList[name]->memberList.begin();
	s = ":" + user->getNickName() + "!" + user->getUserName() + 
		"@127.0.0.1 " + command.front() + " :" + *it +"\r\n";
	for(; it3 != channelManager->channelList[name]->memberList.end(); ++it3)
	{
		reply((*it3)->getFd(), s);
		user->adjacentList[*it3].erase(channelManager->channelList[name]);
		if(user->adjacentList[*it3].empty())
		{
			user->adjacentList.erase(*it3);
		}
		(*it3)->adjacentList[user].erase(channelManager->channelList[name]);
		if((*it3)->adjacentList[user].empty())
		{
			(*it3)->adjacentList.erase(user);
		}
	}
	channelManager->channelList[name]->memberList.erase(user);
	channelManager->channelList[name]->operList.erase(user);
	channelManager->channelList[name]->inviteList.erase(user);
	if(channelManager->channelList[name]->memberList.begin() == channelManager->channelList[name]->memberList.end())
	{
		delete channelManager->channelList[name];
		channelManager->channelList.erase(name);
	}
	user->usedChannelList.erase(name);
}

void Command::invite(const std::vector<std::string> &command, User *user)
{
	NumericReplies numbericReplies(user);
	if(command.size() < 3)
	{
		numbericReplies.needMoreParams(command.front());
		return ;
	}
	if(!user->isLogin())
	{
		numbericReplies.NotRegistered();
		return ;
	}

	std::vector<std::string>::const_iterator it = command.begin() + 1;
	User* target = userManager->findNick(*it);
	if(!target)
	{
		numbericReplies.noSuchNick(*it);
		return ;
	}
	std::string name = (*(it + 1)).substr(1);
	Channel* ch = channelManager->find(name);
	if(!ch || *((*(it + 1)).begin()) != '#')
	{
		numbericReplies.noSuchChannel(*(it + 1));
		return;
	}
	if(channelManager->channelList[name]->memberList.find(user) == channelManager->channelList[name]->memberList.end())
	{
		numbericReplies.notOnChannel(*it);
		return ;
	}
	if(channelManager->channelList[name]->operList.find(user) == channelManager->channelList[name]->operList.end())
	{
		numbericReplies.chanOpPrivsNeeded(*(it + 1));
		return ;
	}
	if(channelManager->channelList[name]->memberList.find(target) != channelManager->channelList[name]->memberList.end())
	{
		numbericReplies.userOnChannel(target->getNickName(), *(it + 1));
		return ;
	}
	if(channelManager->channelList[name]->inviteList.find(target) == channelManager->channelList[name]->inviteList.end())
	{
		channelManager->channelList[name]->inviteList.insert(target);
	}
	reply(user->getFd(), ":ircserv 341 "+ user->getNickName() + " " + target->getNickName() + " :"+ +"\r\n");
	reply(target->getFd(), ":" + user->getNickName() + "!" + user->getUserName() + " INVITE " + target->getNickName() + " :" + *(it + 1) + "\r\n");
}

void Command::topic(const std::vector<std::string> &command, User *user)
{
	NumericReplies numbericReplies(user);
	if(command.size() < 2)
	{
		numbericReplies.needMoreParams(command.front());
		return ;
	}
	if(!user->isLogin())
	{
		numbericReplies.NotRegistered();
		return ;
	}
	std::vector<std::string>::const_iterator it = command.begin() + 1;
	std::string name = (*it).substr(1);
	Channel* ch = channelManager->find(name);
	if(!ch || *((*it).begin()) != '#')
	{
		numbericReplies.noSuchChannel(*it);
		return;
	}
	if(channelManager->channelList[name]->memberList.find(user) == channelManager->channelList[name]->memberList.end())
	{
		numbericReplies.notOnChannel(*it);
		return ;
	}
	if(command.size() == 2)
	{
		if(channelManager->channelList[name]->topic == "")
		{
			reply(user->getFd(), ":ircserv 331 " + user->getNickName() + " " + *it + " :No topic is set.\r\n");
		}
		else
		{
			reply(user->getFd(), ":ircserv 332 " + user->getNickName() + " " + *it + " :" + channelManager->channelList[name]->topic + "\r\n");
		}
		return ;
	}
	else
	{
		if((channelManager->channelList[name]->mode & SIGTOPIC) && channelManager->channelList[name]->operList.find(user) == channelManager->channelList[name]->operList.end())
		{
			numbericReplies.chanOpPrivsNeeded(*it);
			return ;
		}
		std::vector<std::string>::const_iterator it2 = command.begin() + 2;
		std::string target = (*it2).at(0) == ':' ? (*it2).substr(1) : (*it2).substr(0);
		++it2;
		for(; it2 != command.end(); ++it2)
		{
			target += " ";
			target += *it2;
		}
		if(target.length() >= 84)
		{
			target = target.substr(0, 84);
		}
		if(channelManager->channelList[name]->topic == target)
		{
			return ;
		}
		else
		{
			channelManager->channelList[name]->topic = target;
			channelManager->channelList[name]->topicTime = time(NULL);
			std::set<User *>::const_iterator it3 = channelManager->channelList[name]->memberList.begin();
			for(;it3 != channelManager->channelList[name]->memberList.end(); ++it3)
			{
				reply((*it3)->getFd(), ":" + user->getNickName() + "!" + user->getUserName() + "@127.0.0.1 " + *command.begin() + " " + *it + " :" + channelManager->channelList[name]->topic + "\r\n");
			}
		}
	}
}

void Command::mode(const std::vector<std::string> &command, User *user)
{
	NumericReplies numbericReplies(user);
	if(command.size() < 3)
	{
		numbericReplies.needMoreParams(command.front());
		return ;
	}
	if(!user->isLogin())
	{
		numbericReplies.NotRegistered();
		return ;
	}
	std::vector<std::string>::const_iterator it = command.begin() + 1;

	if(*((*it).begin()) != '#')
	{
		if(user->isLogin())
			numbericReplies.unknownCommand(command.front(), "[mode user] is not a recognised command.");
		return;
	}
	std::string name = (*it).substr(1);
	Channel* ch = channelManager->find(name);
	if(!ch)
	{
		numbericReplies.noSuchChannel(*it);
		return;
	}
	if(channelManager->channelList[name]->memberList.find(user) == channelManager->channelList[name]->memberList.end())
	{
		numbericReplies.notOnChannel(*it);
		return ;
	}

	++it;
	std::string argument = (*it).at(0) == '-' || (*it).at(0) == '+' ? (*it).substr(1) : *it;
	bool sign = (*it).at(0) == '-' ? 0 : 1;
	std::string c = (*it).at(0) == '-' ? "-" : "+";
	++it;
	std::string s;
	std::string s2;
	std::string validVar;
	std::vector<std::string> validArg;
	std::string::iterator it2 = argument.begin();
	for(; it2 != argument.end();)
	{
		switch(*it2)
		{
			case 'i': case 't': case 'k': case 'o': case 'l': case '+': case '-':
			++it2;
			break;
			default:
			s += ":ircserv 472 " + user->getNickName() + " " + *it2 + " :is not a recognised channel mode.\r\n";
			argument.erase(it2);
		}
	}

	it2 = argument.begin();
	User* target;
	for(; it2 != argument.end(); ++it2)
	{
		if(*it2 == '+')
		{
			c = "+";
			sign = 1;
			continue;
		}
		else if (*it2 == '-')
		{
			c = "-";
			sign = 0;
			continue;
		}
		switch (*it2)
		{
			case 'i':
			if(channelManager->channelList[name]->operList.find(user) == channelManager->channelList[name]->operList.end())
			{
				s += ":ircserv 482 " + user->getNickName() + " #" + name + " :You must be a channel op or higher to unset channel mode i (inviteonly).\r\n";
				break;
			}
			if(sign == !!(channelManager->channelList[name]->mode & SIGINVITE))
			{
				break;
			}
			if(sign)
			{
				channelManager->channelList[name]->mode |= SIGINVITE;
			}
			else
			{
				channelManager->channelList[name]->mode -= SIGINVITE;
			}
			validVar += c + "i";
			c.clear();
			break;

			case 't':
			if(channelManager->channelList[name]->operList.find(user) == channelManager->channelList[name]->operList.end())
			{
				s += ":ircserv 482 " + user->getNickName() + " #" + name + " :You must be a channel op or higher to set channel mode t (topiclock).\r\n";
				break;
			}
			if(sign == !!(channelManager->channelList[name]->mode & SIGTOPIC))
			{
				break;
			}
			if(sign)
			{
				channelManager->channelList[name]->mode |= SIGTOPIC;
			}
			else
			{
				channelManager->channelList[name]->mode -= SIGTOPIC;
			}
			validVar += c + "t";
			c.clear();
			break;

			case 'k':
			if(it == command.end())
			{
				s += ":ircserv 696 " + user->getNickName() + " #" + name + " :You must specify a parameter for the key mode. Syntax: <key>.\r\n";
				break;
			}
			++it;
			if(channelManager->channelList[name]->operList.find(user) == channelManager->channelList[name]->operList.end())
			{
				s += ":ircserv 482 " + user->getNickName() + " #" + name + " :You must be a channel op or higher to set channel mode k (key).\r\n";
				break;
			}
			if(sign == !!(channelManager->channelList[name]->mode & SIGKEY))
			{
				break;
			}
			if(sign)
			{
				channelManager->channelList[name]->mode |= SIGKEY;
				channelManager->channelList[name]->key = *(it - 1);
			}
			else
			{
				if(channelManager->channelList[name]->key != *(it - 1))
				{
					s += ":ircserv 467 " + user->getNickName() + " #" + name + " :Channel key already set\r\n";
					break;
				}
				channelManager->channelList[name]->key = "";
				channelManager->channelList[name]->mode -= SIGKEY;
			}
			validVar += c + "k";
			validArg.push_back(*(it - 1));
			c.clear();
			break;

			case 'o':
			if(it == command.end())
			{
				s += ":ircserv 696 " + user->getNickName() + " #" + name + " :You must specify a parameter for the op mode. Syntax: <nick>.\r\n";
				break;
			}
			++it;
			if(channelManager->channelList[name]->operList.find(user) == channelManager->channelList[name]->operList.end())
			{
				s += ":ircserv 482 " + user->getNickName() + " #" + name + " :You must be a channel op or higher to set channel mode o (op).\r\n";
				break;
			}
			target = channelManager->userManager->findNick(*(it - 1));
			if(!target)
			{
				s += ":ircserv 401 " + user->getNickName() + " " + *(it - 1) + " :No such nick\r\n";
				break;
			}
			if(channelManager->channelList[name]->operList.find(target) == channelManager->channelList[name]->operList.end())
			{
				if(sign)
				{
					channelManager->channelList[name]->operList.insert(target);
				}
				else
				{
					break;
				}
			}
			else
			{
				if(!sign)
				{
					channelManager->channelList[name]->operList.erase(target);
				}
				else
				{
					break;
				}
			}
			validVar += c + "o";
			validArg.push_back(*(it - 1));
			c.clear();
			break;

			case 'l':
			if(c == "+" && it == command.end())
			{
				s += ":ircserv 696 " + user->getNickName() + " #" + name + " * :You must specify a parameter for the limit mode. Syntax: <limit>.\r\n";
				break;
			}
			++it;
			if(channelManager->channelList[name]->operList.find(user) == channelManager->channelList[name]->operList.end())
			{
				s += ":ircserv 482 " + user->getNickName() + " #" + name + " :You must be a channel op or higher to set channel mode l (limit).\r\n";
				break;
			}
			if(!sign && !(channelManager->channelList[name]->mode & SIGLIMIT))
			{
				break;
			}
			if(sign)
			{
				channelManager->channelList[name]->mode |= SIGLIMIT;
				long n = std::strtol((*(it - 1)).c_str(), NULL, 10);
				if(errno == ERANGE)
				{
					s += ":ircserv 696 " + user->getNickName() + " #" + name + " " + *it2 + " " + *(it - 1) + " " + ":You must specify a parameter for the limit mode. Syntax: <limit>.\r\n";
					break;
				}
				else if (n <= 0)
				{
					s += ":ircserv 696 " + user->getNickName() + " #" + name + " " + *it2 + " " + *(it - 1) + " " + ":Invalid limit mode parameter. Syntax: <limit>.\r\n";
					break;
				}
				channelManager->channelList[name]->limit = n;
			}
			else
			{
				channelManager->channelList[name]->mode -= SIGLIMIT;
				channelManager->channelList[name]->limit = LONG_MAX;
			}
			validVar += c + "l";
			c.clear();
		}
	}

	if(validVar.empty())
	{
		reply(user->getFd(), s);
		return ;
	}

	s2 = ":" + user->getNickName() + "!" + user->getUserName() + "@127.0.0.1 " + *command.begin() + " #" + name + " ";
	if(validArg.empty())
	{
		s2 += ":" + validVar + "\r\n";
	}
	else
	{
		s2 += validVar;
		std::vector<std::string>::const_iterator it3 = validArg.begin();
		for(; it3 != validArg.end(); ++it3)
		{
			s2 += it3 + 1 == validArg.end() ? " :" : " ";
			s2 += *it3;
		}
		s2 += "\r\n";
	}
	s += s2;

	reply(user->getFd(), s);
	std::set<User *>::const_iterator it3;
	it3 = channelManager->channelList[name]->memberList.begin();
	for(; it3 != channelManager->channelList[name]->memberList.end(); ++it3)
	{
		if((*it3)->getFd() != user->getFd())
			reply((*it3)->getFd(), s2);
	}
}

void Command::firstMessage(User *user)
{
	std::string s = ":ircserv 001 " + user->getNickName() + " :Welcome to the Localnet IRC Network "+ user->getNickName() + "!" + user->getUserName() + "@127.0.0.1\r\n";
	reply(user->getFd(), s);
}
