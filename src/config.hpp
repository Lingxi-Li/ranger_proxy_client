// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#pragma once

#include "server_config.hpp"
#include "singleton.hpp"

class Config
 : public Singleton<Config> {
  friend class Singleton<Config>;
  Config();

public:
  unsigned local_port = 0;
  std::vector<ServerConfig> servers;

private:
  static std::istringstream RemoveComments(std::istream& cfg);
  static unsigned ReadLocalPort(std::istream& cfg);
};
