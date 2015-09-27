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

// Backed up by a single thread. Handler invocations are serialized.
class NetworkIoService
 : public boost::asio::io_service
 , public Singleton<NetworkIoService> {
  friend class Singleton<NetworkIoService>;
  // VC15 workaround. If a work object is to be constructed by using a new
  // expression, the program enters a seemingly infinite loop. So, make it a
  // class member here.
  work work_;
  NetworkIoService()
   : io_service(1)
   , work_(*this) {
    std::size_t(io_service::*p_run)() = &io_service::run;
    // To be cleaned by system at process termination.
    new std::thread(p_run, this);
  }
  // No more thread should be backing up this service to break its
  // single-threaded nature.
  using io_service::run;
  using io_service::run_one;
  using io_service::poll;
  using io_service::poll_one;
};
