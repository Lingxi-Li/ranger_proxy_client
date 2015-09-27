// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#pragma once

#include "processor_config.hpp"
#include "singleton.hpp"

class ServerConnector
 : public Singleton<ServerConnector> {
  friend class Singleton<ServerConnector>;
  ServerConnector();

public:
  void AsyncConnect(socket_ptr p_client_socket) const;

private:
  void ResolveServers();
  void OnConnected(socket_ptr p_client_socket, socket_ptr p_server_socket,
    unsigned idx, const error_code& err, tcp::resolver::iterator it) const;

  std::vector<tcp::resolver::iterator> endpoint_it_;
  std::vector<ProcessorConfig> processor_cfg_;
  std::vector<unsigned> server_id_;
  mutable unsigned idx_ = 0;
};
