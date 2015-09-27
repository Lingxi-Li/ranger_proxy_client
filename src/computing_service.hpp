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

class ComputingService
 : public boost::asio::io_service
 , public Singleton<ComputingService> {
  friend class Singleton<ComputingService>;
  static const unsigned NUM_THREADS = 5;
  // VC15 workaround. If a work object is to be constructed by using a new
  // expression, the program enters a seemingly infinite loop. So, make it a
  // class member here.
  work work_;
  ComputingService()
   : io_service(NUM_THREADS)
   , work_(*this) {
    std::size_t(io_service::*p_run)() = &io_service::run;
    for (unsigned i = 0; i < NUM_THREADS; ++i) {
      // To be cleaned by system at process termination.
      new std::thread(p_run, this);
    }
  }
};
