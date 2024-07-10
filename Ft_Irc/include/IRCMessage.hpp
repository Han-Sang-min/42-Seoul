#pragma once
#ifndef IRCMESSAGE_HPP
#define IRCMESSAGE_HPP
#include <string>
#include <map>
#include <vector>
#include <stdexcept>

class User;
class Channel;

class IRCMessage {
private:
    std::map<std::string, std::string> tags; // key & value
    std::string source;
    std::string command;
    std::vector<std::string> parameters;

    std::string createTags(const std::map<std::string, std::string>& tags) const;
    std::string createSource(const std::string& source) const;
    std::string createParameters(const std::vector<std::string>& parameters) const;

    std::string concatenateVectorContent(const std::vector<std::string>& vector);

    std::string creatMessageToSendToChannel(User *user, Channel *receivChannel, const std::string& command, const std::vector<std::string>& messages);
    std::string creatMessageToSendToUser(User *user, User *receiver, const std::string& command, const std::vector<std::string>& vector);
public:
    IRCMessage();

    void setTags(const std::map<std::string, std::string>& t);
    void setSource(const std::string& s);
    void setCommand(const std::string& c);
    
    void addParameter(const std::string& p1, const std::string& p2);
    void addParameter(const std::string& p1, const std::string& p2, const std::string& p3);
    void addParameter(const std::string& p1, const std::string& p2, const std::string& p3, const std::string& p4);

    std::string generateMessage() const; //private 고려
    void sendMessageToUser(User* user) const;
    void pongMessage(User* user) const;

    void privmsgHandler(User *user, User *receiver, const std::string& command, const std::vector<std::string>& vector);
    void privmsgHandler(User *user, Channel *receiver, const std::string& command, const std::vector<std::string>& vector);
};
#endif
