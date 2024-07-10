#pragma once
#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# define SIGINVITE 1
# define SIGTOPIC 2
# define SIGKEY 4
# define SIGLIMIT 8

class Core Channel
{
	public:
	typedef std::set<User *> memberSet;
	typedef std::set<User *> operSet;
	typedef std::set<User *> inviteSet;
	public:
		Channel(const std::string& name);
		~Channel();

		memberSet memberList;
		operSet operList;
		inviteSet inviteList;
		int mode;
		std::string key;
		std::string topic;
		unsigned long limit;
		time_t topicTime;
		const std::string& getChannelName() const;
	private:
		std::string name;

		Channel();
    	Channel(const Channel &copy);
		Channel& operator=(const Channel &assign);
};

#endif
