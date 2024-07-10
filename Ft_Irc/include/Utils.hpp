#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <ostream>

// tosSring 함수
template <class T>
std::string str(const T& a){
  std::ostringstream oss;
  oss << a;
  return oss.str();
}

void trim(std::string& s, const std::string& t);
void mergeSpace(std::string& s);
void tokenize(std::string &str, char const &delim,
            std::vector<std::string> &out);
void reply(const int& fd, const std::string& s);
#endif
