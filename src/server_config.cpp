// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#include "server_config.hpp"

#include "macro_def.hpp"
#include "util.hpp"

ServerConfig::ServerConfig(std::istream& in) {
  std::string line;
  // Read lines until blank line or EOF.
  while (std::getline(in, line), line.size()) {
    std::string key, value;
    std::tie(key, value) = GetKeyValue(line);
    // Switch on key.
    key == REMOTE_HOST    ? (void)(host     = std::move(value)) :
    key == REMOTE_SERVICE ? (void)(service  = std::move(value)) :
                            processor_cfg.ParseConfigItem(key, value);
  }
  in >> std::ws;
}

std::ostream& operator <<(std::ostream& os, const ServerConfig& cfg) {
  return os << REMOTE_HOST ": " << cfg.host << "\n" REMOTE_SERVICE ": " 
            << cfg.service << '\n' << cfg.processor_cfg;
}
