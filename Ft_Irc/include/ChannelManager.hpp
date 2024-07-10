#pragma once
#ifndef CHANNELMANAGER_HPP
# define CHANNELMANAGER_HPP

typedef std::map<std::string ,Channel *> channelMap;

class Core ChannelManager
{
	public:
		Channel *find(const std::string& channel) const;
		static bool isValidChannel(const std::string& channel);

		UserManager *userManager;
		channelMap channelList;
		ChannelManager();
		~ChannelManager();
	private:
		ChannelManager & operator=(const ChannelManager &assign);
		ChannelManager(const ChannelManager &copy);
};

#endif
