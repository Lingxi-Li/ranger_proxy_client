// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#include "server_connector.hpp"

#include "config.hpp"
#include "initiator.hpp"
#include "macro_def.hpp"
#include "network_io_service.hpp"
#include "util.hpp"

ServerConnector::ServerConnector() {
  ResolveServers();
}

void ServerConnector::ResolveServers() {
  tcp::resolver resolver(NetworkIoService::Get());
  error_code err;
  unsigned i = 0;
  // Resolve each server.
  for (auto& server_info : Config::Get().servers) {
    std::cout << "Server " << ++i << " config\n"
              << server_info << std::endl;
    auto it = resolver.resolve(
      tcp::resolver::query(server_info.host, server_info.service), err);
    if (it == decltype(it)()) {
      LogError("Resolve failed. This server won't be used", err, false);
      std::cout << '\n';
    }
    else {
      std::cout << "Resolve succeeded." PARA_END;
      endpoint_it_.push_back(std::move(it));
      processor_cfg_.push_back(server_info.processor_cfg);
      server_id_.push_back(i);
    }
  }
  if (endpoint_it_.empty())
    throw std::runtime_error(ERR_MSG_NO_RESOLVED_SERVER);
  std::cout << endpoint_it_.size() << " server(s) resolved." PARA_END;
}

void ServerConnector::AsyncConnect(socket_ptr p_client_socket) const {
  using namespace std::placeholders;
  auto p_server_socket = std::make_shared<tcp::socket>(NetworkIoService::Get());
  unsigned idx = idx_;
  idx_ = (idx_ + 1) % endpoint_it_.size();  // Round-robin.
  auto& server_socket = *p_server_socket;
  boost::asio::async_connect(server_socket, endpoint_it_[idx],
    std::bind(&ServerConnector::OnConnected, this, std::move(p_client_socket),
      std::move(p_server_socket), idx, _1, _2));
}

void ServerConnector::OnConnected(socket_ptr p_client_socket,
 socket_ptr p_server_socket, unsigned idx, const error_code& err,
 tcp::resolver::iterator it) const {
  if (!err) {
    StartInitProcedure(std::move(p_client_socket), std::move(p_server_socket),
      processor_cfg_[idx]);
  }
  else {
    LogError("Failed to connect to Server " + 
      std::to_string(server_id_[idx]), err);
    std::cout << "  Retry (possibly to a different server)." << std::endl;
    AsyncConnect(std::move(p_client_socket));
  }
}
