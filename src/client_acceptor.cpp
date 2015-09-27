// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#include "client_acceptor.hpp"

#include "config.hpp"
#include "macro_def.hpp"
#include "network_io_service.hpp"
#include "server_connector.hpp"
#include "util.hpp"

ClientAcceptor::ClientAcceptor()
 : acceptor_ipv4_(NetworkIoService::Get(), tcp::endpoint(
                  tcp::v4(), (unsigned short)(Config::Get().local_port)))
 , acceptor_ipv6_(NetworkIoService::Get(), tcp::endpoint(
                  tcp::v6(), (unsigned short)(Config::Get().local_port))) {
  std::cout << LOCAL_PORT ": " << Config::Get().local_port << PARA_END;
}

void ClientAcceptor::ChainedAsyncAccept(tcp protocol) {
  auto p_client_socket = std::make_shared<tcp::socket>(NetworkIoService::Get());
  auto& acceptor = protocol == tcp::v4() ? acceptor_ipv4_ : acceptor_ipv6_;
  auto& client_socket = *p_client_socket;
  acceptor.async_accept(client_socket,
    std::bind(&ClientAcceptor::OnAccepted,
      this, std::move(p_client_socket), std::placeholders::_1));
}

void ClientAcceptor::OnAccepted(socket_ptr p_client_socket,
 const error_code& err) {
  ChainedAsyncAccept(p_client_socket->local_endpoint().protocol());
  if (!err) {
    //LogMessage("Connection accepted", p_client_socket->remote_endpoint());
    ServerConnector::Get().AsyncConnect(std::move(p_client_socket));
  }
  else {
    LogError("Failed to accept connection", err);
  }
}
