// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#include "client_acceptor.hpp"
#include "config.hpp"
#include "computing_service.hpp"
#include "macro_def.hpp"
#include "network_io_service.hpp"
#include "server_connector.hpp"

int main() {
  GUARD_EXCEPTION_BEGIN
  std::cout << COPYRIGHT_NOTICE "\n" RULE_70 PARA_END;

  // Pre-initialize singletons to smooth following run. Also in case
  // initialization of static local variables is not thread-safe for
  // non-compliant compilers.
  (void)(Config::Get());
  (void)(NetworkIoService::Get());
  (void)(ComputingService::Get());
  (void)(ClientAcceptor::Get());
  (void)(ServerConnector::Get());
  std::cout << "Up and running...\n" RULE_70 PARA_END;
  
  ClientAcceptor::Get().ChainedAsyncAccept(tcp::v4());
  ClientAcceptor::Get().ChainedAsyncAccept(tcp::v6());

  ComputingService::Get().run();  // Join in powering up computing service.
  GUARD_EXCEPTION_END
  std::cout << "\nPress <Enter> to terminate." << std::flush;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
