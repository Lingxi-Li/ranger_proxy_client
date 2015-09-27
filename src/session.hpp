// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#pragma once

#include "processor.hpp"

class SessionBundle {
public:
  SessionBundle(const socket_ptr& p_read_socket, 
    const socket_ptr& p_write_socket, unique_processor_ptr&& p_processor);
  SessionBundle(socket_ptr&& p_read_socket, socket_ptr&& p_write_socket,
    unique_processor_ptr&& p_processor);

  socket_ptr p_read_socket;
  socket_ptr p_write_socket;
  read_buffer r_buffer = {};
  unique_processor_ptr p_processor;
};

using session_bundle_ptr = std::shared_ptr<SessionBundle>;

void ChainedAsyncRead(session_bundle_ptr p_bundle);
