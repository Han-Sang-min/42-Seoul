#pragma once
#ifndef NUMERICREPLIES_HPP
#define NUMERICREPLIES_HPP
#include <string>
#include "IRCMessage.hpp"
#include "User.hpp"

class IRCMessage;

enum IRCErrorCode {
    ERR_NEEDMOREPARAMS = 461,
    ERR_NOSUCHCHANNEL = 403,
    ERR_CHANOPRIVSNEEDED = 482,
    ERR_USERNOTINCHANNEL = 441,
    ERR_NOTONCHANNEL = 442,
    ERR_UNKNOWNCOMMAND = 421,
	
    ERR_TOOMANYCHANNELS = 405,
    ERR_BADCHANNELKEY = 475,
    ERR_BANNEDFROMCHAN = 474,
    ERR_CHANNELISFULL = 471,
    ERR_INVITEONLYCHAN = 473,
    ERR_BADCHANMASK = 476,

    RPL_TOPIC = 332,
    RPL_TOPICWHOTIME = 333,
    RPL_NAMREPLY = 353,
    RPL_ENDOFNAMES = 366,
    RPL_INVITING = 341,
    ERR_USERONCHANNEL = 443,
    
	RPL_NOTOPIC = 331,
    ERR_NOSUCHNICK = 401,
    ERR_NOSUCHSERVER = 402,
    ERR_CANNOTSENDTOCHAN = 404,
    ERR_TOOMANYTARGETS = 407,
    ERR_NORECIPIENT = 411,

    ERR_NOTEXTTOSEND = 412,
    ERR_NOTOPLEVEL = 413,
    ERR_WILDTOPLEVEL = 414,
    RPL_AWAY = 301,
    ERR_ERRONEUSNICKNAME = 432,
    ERR_PASSWDMISMATCH = 462,
    ERR_NOTREGISTERED = 451,
    ERR_NICKNAMEINUSE = 433
};



class NumericReplies {
private:
	NumericReplies();
    User* user;

public:
    NumericReplies(User* u);

    void needMoreParams(const std::string& command);
    void noSuchChannel(const std::string& channelName);
    void chanOpPrivsNeeded(const std::string& channelName);
    void userNotInChannel(const std::string& nickname, const std::string& channelName);
    void notOnChannel(const std::string& channelName);
	void tooManyChannels(const std::string& channelName);
    void badChannelKey(const std::string& channelName);
    void bannedFromChan(const std::string& channelName);
    void channelIsFull(const std::string& channelName);
    void inviteOnlyChan(const std::string& channelName);
    void badChanMask(const std::string& channelName);
	void replyTopic(const std::string& channelName, const std::string& topic);
    void replyTopicWhoTime(const std::string& channelName, const std::string& who, const std::string& time);
    void nameReply(const std::string& channelType, const std::string& channelName, const std::string& names);
    void endOfNames(const std::string& channelName);
    void inviting(const std::string& nickName, const std::string& channelName);
    void userOnChannel(const std::string& nickName, const std::string& channelName);
	void noTopicSet(const std::string& channelName);
    void noSuchNick(const std::string& nickname);
    void noSuchServer(const std::string& serverName);
    void cannotSendToChannel(const std::string& channelName);
    void tooManyTargets(const std::string& target);
    void noRecipient(const std::string& command);
    void noTextToSend();
    void noTopLevel(const std::string& mask);
    void wildTopLevel(const std::string& mask);
    void away(const std::string& nickname, const std::string& awayMessage);
    void erroneusNickname(const std::string& nickname);
    void NicknameIsAlreadInUse(const std::string& nickname);
    void PasswdMisMatch();
    void NotRegistered();
    void unknownCommand(const std::string& command, const std::string& errMsg);
    void unknownCommand(const std::string& command);

    void closingLinkBufferExceeded();
    
};
#endif
