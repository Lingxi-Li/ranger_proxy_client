// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#include "util.hpp"

#include "macro_def.hpp"

std::pair<std::string, std::string> GetKeyValue(const std::string& line) {
  auto sign_pos = line.find('=');
  if (sign_pos == line.npos)
    throw std::invalid_argument(ERR_MSG_MISSING_EQUAL_SIGN);
  return { line.substr(0, sign_pos), line.substr(sign_pos + 1) };
}

std::string DateTime() {
  std::string str("09-27 11:07:00");
  str.push_back('\0');
  auto t = std::time(nullptr);
  std::strftime(&str[0], str.size(), "%m/%d %T", std::localtime(&t));
  str.pop_back();  // Remove redundant terminating null.
  return str;
}

void LogError(const std::string& msg, const error_code& err, bool with_time) {
  if (with_time) std::cout << DateTime() << ' ';
  std::cout << msg << ". Error code: " << err << std::endl;
}

void LogError(const std::string& msg, const tcp::endpoint& endpoint,
 const error_code& err, bool with_time) {
  if (with_time) std::cout << DateTime() << ' ';
  std::cout << msg << ". Endpoint: " << endpoint << ". Error code: " << err 
            << std::endl;
}

void LogMessage(const std::string& msg, const tcp::endpoint& endpoint,
 bool with_time) {
  if (with_time) std::cout << DateTime() << ' ';
  std::cout << msg << ". Endpoint: " << endpoint << std::endl;
}
