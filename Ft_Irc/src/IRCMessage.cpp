#include "../include/Server.hpp"

IRCMessage::IRCMessage() {}

std::string IRCMessage::createTags(const std::map<std::string, std::string>& tags) const {
    if (tags.empty()) return "";

        std::string result = "@";
        for (std::map<std::string, std::string>::const_iterator it = tags.begin(); it != tags.end(); ++it) {
            if (it != tags.begin()) result += ";";
            result += it->first;
            if (!it->second.empty()) {
                result += "=" + it->second;
            }
        }
        result += " ";
        return result;
}

std::string IRCMessage::createSource(const std::string& source) const {
    return ":" + source;
}

std::string IRCMessage::createParameters(const std::vector<std::string>& parameters) const {
    std::string result;
        for (size_t i = 0; i < parameters.size(); ++i) {
            if (i == parameters.size() - 1) {
                result += ":" + parameters[i];
            } else {
                result += parameters[i] + " ";
            }
        }
        return result;
}

void IRCMessage::setTags(const std::map<std::string, std::string>& t) {
    tags = t;
}

void IRCMessage::setSource(const std::string& s) {
    source = s;
}

void IRCMessage::setCommand(const std::string& c) {
    command = c;
}

void IRCMessage::addParameter(const std::string& p1, const std::string& p2) {
    parameters.push_back(p1);
	parameters.push_back(p2);
}

void IRCMessage::addParameter(const std::string& p1, const std::string& p2, const std::string& p3) {
    parameters.push_back(p1);
	parameters.push_back(p2);
	parameters.push_back(p3);
}

void IRCMessage::addParameter(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4) {
    parameters.push_back(p1);
	parameters.push_back(p2);
	parameters.push_back(p3);
	parameters.push_back(p4);
}

std::string IRCMessage::generateMessage() const {
    std::string message = createTags(tags)  +
                              createSource(source) + " " +
                              command + " " +
                              createParameters(parameters) + "\r\n";

        if (message.size() > 512) {
            return "Commend error: Message size is over.\r\n";
        }
        return message;
}

void IRCMessage::sendMessageToUser(User* user) const {
    std::string message = generateMessage();
    user->send(message);
}

std::string IRCMessage::concatenateVectorContent(const std::vector<std::string>& vector) {
    std::string message;

    std::vector<std::string>::const_iterator it = vector.begin() + 2;
    for(; it != vector.end(); ++it)
    {
        message += *it;
        if(it + 1 != vector.end()) message += ' ';
    }
    return message;
}

std::string IRCMessage::creatMessageToSendToUser(User *user, User *receiver, const std::string& command, const std::vector<std::string>& vector) {
    std::string message = ":" + user->getNickName() + "!" + user->getUserName() + " " + command + " " + receiver->getNickName() + " ";
    message += concatenateVectorContent(vector);
    message += "\r\n";

    return message;
}

void IRCMessage::privmsgHandler(User *user, User *receiver, const std::string& command, const std::vector<std::string>& vector) {
    const std::string message = creatMessageToSendToUser(user, receiver, command, vector);
    reply(receiver->getFd(), message);
}

std::string IRCMessage::creatMessageToSendToChannel(User *user, Channel *receivChannel, const std::string& command, const std::vector<std::string>& messages) {
        std::string message = ":" + user->getNickName() + "!" + user->getUserName() + " " + command + " #" + receivChannel->getChannelName() + " :";
        message += concatenateVectorContent(messages);
        message += "\r\n";

        return message;
}

void IRCMessage::privmsgHandler(User *user, Channel *receivChannel, const std::string& command, const std::vector<std::string>& messages) {
    std::set<User *>::const_iterator memberInChennal = receivChannel->memberList.begin();
    for(; memberInChennal != receivChannel->memberList.end(); ++memberInChennal)
    {
        if((*memberInChennal)->getNickName() != user->getNickName())
        {
            const std::string message = creatMessageToSendToChannel(user, receivChannel, command, messages);
            reply((*memberInChennal)->getFd(), message);
        }
    }
}

void IRCMessage::pongMessage(User* user) const {
    std::string message = ":ircserv PONG ircserv :ircserv\r\n";
	reply(user->getFd(), message);
}
