// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#pragma once

#include "common.hpp"
#include "singleton.hpp"

class ClientAcceptor
 : public Singleton<ClientAcceptor> {
  friend class Singleton<ClientAcceptor>;
  ClientAcceptor();

public:
  void ChainedAsyncAccept(tcp protocol);

private:
  void OnAccepted(socket_ptr client_socket, const error_code& err);

  tcp::acceptor acceptor_ipv4_;
  tcp::acceptor acceptor_ipv6_;
};
