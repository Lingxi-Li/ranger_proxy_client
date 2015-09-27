// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#pragma once

#include "processor_config.hpp"

class ServerConfig {
public:
  std::string host;
  std::string service;
  ProcessorConfig processor_cfg;

  ServerConfig(std::istream& in);
};

std::ostream& operator <<(std::ostream& os, const ServerConfig& cfg);
