#include "../include/Server.hpp"
#include <cstddef>
#include <stdexcept>

NumericReplies::NumericReplies(User* u) : user(u) {
    if (user == NULL)
        throw std::runtime_error("User fd isn't normal");
}

// 461
void NumericReplies::needMoreParams(const std::string& command) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_NEEDMOREPARAMS));
    if (user->getNickName() != "")
        message.addParameter(user->getNickName(), command, "Need more parameters");
    else
        message.addParameter("*", command, "Need more parameters");
    message.sendMessageToUser(user);
}

// 403
void NumericReplies::noSuchChannel(const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_NOSUCHCHANNEL));
    message.addParameter(user->getNickName(), channelName, "No such channel");
    message.sendMessageToUser(user);
}

// 482
void NumericReplies::chanOpPrivsNeeded(const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_CHANOPRIVSNEEDED));
    message.addParameter(user->getNickName(), channelName, "You're not channel operator");
    message.sendMessageToUser(user);
}

// 441
void NumericReplies::userNotInChannel(const std::string& nickname, const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_USERNOTINCHANNEL));
    message.addParameter(user->getNickName(), nickname,channelName, "They aren't on that channel");
    message.sendMessageToUser(user);
}

// 442
void NumericReplies::notOnChannel(const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_NOTONCHANNEL));
    message.addParameter(user->getNickName(), channelName, "You're not on that channel");
    message.sendMessageToUser(user);
}

void NumericReplies::closingLinkBufferExceeded() {
    user->send("ERROR :Closing link: (" + user->getUserName() + "@127.0.0.1) [recv buffer exceeded]\r\n");
}

// 421
void NumericReplies::unknownCommand(const std::string& command) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_UNKNOWNCOMMAND));
    message.addParameter(user->getNickName(), command, "Unknown command");
    message.sendMessageToUser(user);
}

// 421
void NumericReplies::unknownCommand(const std::string& command, const std::string& errMsg) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_UNKNOWNCOMMAND));
    message.addParameter(user->getNickName(), command, errMsg);
    message.sendMessageToUser(user);
}

// 405
void NumericReplies::tooManyChannels(const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_TOOMANYCHANNELS));
    message.addParameter(user->getNickName(), channelName, "You have joined too many channels");
    message.sendMessageToUser(user);
}

// 475
void NumericReplies::badChannelKey(const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_BADCHANNELKEY));
    message.addParameter(user->getNickName(), channelName, "Cannot join channel (+k) - bad key");
    message.sendMessageToUser(user);
}

// 474
void NumericReplies::bannedFromChan(const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_BANNEDFROMCHAN));
    message.addParameter(user->getNickName(), channelName, "Cannot join channel (+b) - you are banned");
    message.sendMessageToUser(user);
}

// 471
void NumericReplies::channelIsFull(const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_CHANNELISFULL));
    message.addParameter(user->getNickName(), channelName, "Cannot join channel (+l) - channel is full");
    message.sendMessageToUser(user);
}

// 473
void NumericReplies::inviteOnlyChan(const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_INVITEONLYCHAN));
    message.addParameter(user->getNickName(), channelName, "Cannot join channel (+i) - invite only");
    message.sendMessageToUser(user);
}

// 476
void NumericReplies::badChanMask(const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_BADCHANMASK));
    message.addParameter(user->getNickName(), channelName, "Bad channel mask");
    message.sendMessageToUser(user);
}

// 332
void NumericReplies::replyTopic(const std::string& channelName, const std::string& topic) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(RPL_TOPIC));
    message.addParameter(user->getNickName(), channelName, topic);
    message.sendMessageToUser(user);
}

// 333
void NumericReplies::replyTopicWhoTime(const std::string& channelName, const std::string& who, const std::string& time) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(RPL_TOPICWHOTIME));
    message.addParameter(user->getNickName(), channelName, who, time);
    message.sendMessageToUser(user);
}

// 353
void NumericReplies::nameReply(const std::string& channelType, const std::string& channelName, const std::string& names) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(RPL_NAMREPLY));
    message.addParameter(user->getNickName(), channelType, channelName, names);
    message.sendMessageToUser(user);
}

// 366
void NumericReplies::endOfNames(const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(RPL_ENDOFNAMES));
    message.addParameter(user->getNickName(), channelName, "End of /NAMES list.");
    message.sendMessageToUser(user);
}

// 341
void NumericReplies::inviting(const std::string& nickName, const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(RPL_INVITING));
    message.addParameter(user->getNickName(), nickName, channelName);
    message.sendMessageToUser(user);
}

// 443
void NumericReplies::userOnChannel(const std::string& nickName, const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_USERONCHANNEL));
    message.addParameter(user->getNickName(), nickName, channelName, "is already on channel");
    message.sendMessageToUser(user);
}

// 331
void NumericReplies::noTopicSet(const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(RPL_NOTOPIC));
    message.addParameter(user->getNickName(), channelName, "No topic is set");
    message.sendMessageToUser(user);
}


// 401
void NumericReplies::noSuchNick(const std::string& nickname) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_NOSUCHNICK));
    message.addParameter(user->getNickName(), nickname, "No such nick");
    message.sendMessageToUser(user);
}

// 402
void NumericReplies::noSuchServer(const std::string& serverName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_NOSUCHSERVER));
    message.addParameter(user->getNickName(), serverName, "No such server");
    message.sendMessageToUser(user);
}

// 404
void NumericReplies::cannotSendToChannel(const std::string& channelName) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_CANNOTSENDTOCHAN));
    message.addParameter(user->getNickName(), channelName, "Cannot send to channel");
    message.sendMessageToUser(user);
}

// 407
void NumericReplies::tooManyTargets(const std::string& target) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_TOOMANYTARGETS));
    message.addParameter(user->getNickName(), target, "Too many targets");
    message.sendMessageToUser(user);
}

// 411
void NumericReplies::noRecipient(const std::string& command) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_NORECIPIENT));
    message.addParameter(user->getNickName(), command, "No recipient given");
    message.sendMessageToUser(user);
}

// 412
void NumericReplies::noTextToSend() {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_NOTEXTTOSEND));
    message.addParameter(user->getNickName(), "No text to send");
    message.sendMessageToUser(user);
}

// 413
void NumericReplies::noTopLevel(const std::string& mask) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_NOTOPLEVEL));
    message.addParameter(user->getNickName(), mask, "No toplevel domain specified");
    message.sendMessageToUser(user);
}

// 414
void NumericReplies::wildTopLevel(const std::string& mask) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_WILDTOPLEVEL));
    message.addParameter(user->getNickName(), mask, "Wildcard in toplevel domain");
    message.sendMessageToUser(user);
}

// 301
void NumericReplies::away(const std::string& nickname, const std::string& awayMessage) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(RPL_AWAY));
    message.addParameter(user->getNickName(), nickname, awayMessage);
    message.sendMessageToUser(user);
}

// 432
void NumericReplies::erroneusNickname(const std::string& nickname) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_ERRONEUSNICKNAME));
    if (user->getNickName() != "")
        message.addParameter(user->getNickName(), nickname, "Erroneus nickname");
    else
        message.addParameter("*", nickname, "Erroneus nickname");
    message.sendMessageToUser(user);
}

//433
void NumericReplies::NicknameIsAlreadInUse(const std::string& nickname) {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_NICKNAMEINUSE));
    if (user->getNickName() != "")
        message.addParameter(user->getNickName(), nickname, "Nickname is already in use.");
    else
        message.addParameter("*", nickname, "Nickname is already in use.");
    message.sendMessageToUser(user);
}

//462
void NumericReplies::PasswdMisMatch() {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_PASSWDMISMATCH));
    message.addParameter(user->getNickName(), "You may not reregister");
    message.sendMessageToUser(user);
}

//451
void NumericReplies::NotRegistered() {
    IRCMessage message;
    message.setSource(serverInstance->getServerName());
    message.setCommand(str<int>(ERR_NOTREGISTERED));
    message.addParameter(user->getNickName(), "You have not registered");
    message.sendMessageToUser(user);
}
