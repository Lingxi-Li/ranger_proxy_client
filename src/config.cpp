// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#include "config.hpp"

#include "macro_def.hpp"
#include "util.hpp"

Config::Config() {
  std::ifstream raw_cfg(CONFIG);
  if (!raw_cfg.is_open())
    throw std::invalid_argument(ERR_MSG_CANNOT_OPEN_CONFIG);
  auto cfg = RemoveComments(raw_cfg);
  local_port = ReadLocalPort(cfg);
  while (!cfg.eof()) {
    servers.push_back(ServerConfig(cfg));
  }
}

unsigned Config::ReadLocalPort(std::istream& cfg) {
  cfg >> std::ws;
  // First non-blank line or EOF.
  std::string line;
  if (!std::getline(cfg, line))
    throw std::invalid_argument(ERR_MSG_EMPTY_CONFIG);
  cfg >> std::ws;
  std::string key, value;
  std::tie(key, value) = GetKeyValue(line);
  if (key != LOCAL_PORT)
    throw std::invalid_argument(ERR_MSG_LOCAL_PORT_MUST_COME_FIRST);
  return static_cast<unsigned>(std::stoul(value));
}

std::istringstream Config::RemoveComments(std::istream& cfg) {
  std::string line, comment_free;
  // Read lines until EOF.
  while (std::getline(cfg, line)) {
    line += '\n';
    if (line[0] != '#') comment_free += line;
  }
  return std::istringstream(comment_free);
}
