// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#pragma once

#include "common.hpp"

std::pair<std::string, std::string> GetKeyValue(const std::string& line);
std::string DateTime();
void LogError(const std::string& msg, const error_code& err,
  bool with_time = true);
void LogError(const std::string& msg, const tcp::endpoint& endpoint,
  const error_code& err, bool with_time = true);
void LogMessage(const std::string& msg, const tcp::endpoint& endpoint,
  bool with_time = true);
