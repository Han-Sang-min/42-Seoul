#pragma once
#ifndef COMMAND_HPP
#define COMMAND_HPP

typedef std::set<int> commandSet;

/// @brief 커맨드 클래스
class Core Command
{
private:
    Command(Command const& obj);
    Command& operator = (Command const& obj);
    std::map<std::string, void (Command::*)(const std::vector<std::string> &, User *)> commandSwitch;
public:
    const std::map<std::string, void (Command::*)(const std::vector<std::string> &, User *)>& getCommandSwitch() const;

	commandSet commandList;

	void pass(const std::vector<std::string> &command, User *user);
	void nick(const std::vector<std::string> &command, User *user);
	void user(const std::vector<std::string> &command, User *user);
	void join(const std::vector<std::string> &command, User *user);
	void privmsg(const std::vector<std::string> &command, User *user);
	void ping(const std::vector<std::string> &command, User *user);
	void quit(const std::vector<std::string> &command, User *user);
	void info(const std::vector<std::string> &command, User *user);
	void kick(const std::vector<std::string> &command, User *user);
	void part(const std::vector<std::string> &command, User *user);
	void invite(const std::vector<std::string> &command, User *user);
	void topic(const std::vector<std::string> &command, User *user);
	void mode(const std::vector<std::string> &command, User *user);
	void firstMessage(User *user);

    Command();
    ~Command();

	ChannelManager *channelManager;
	UserManager *userManager;
};

#endif
