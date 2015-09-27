// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#include "initiator.hpp"

#include "processor_aes_cfb128.hpp"
#include "session.hpp"
#include "util.hpp"

namespace {

using ivec_seed_ptr = std::shared_ptr<std::uint32_t>;

void OnIvecSeedRead(socket_ptr p_client_socket, socket_ptr p_server_socket,
 const ProcessorConfig& cfg, ivec_seed_ptr p_seed, const error_code& err,
 std::size_t bytes_read) {
  if (bytes_read == 4) {
    ChainedAsyncRead(std::make_shared<SessionBundle>(p_client_socket,
      p_server_socket, std::make_unique<Processor_AES_CFB128>(
        cfg.key_str, *p_seed, AES_ENCRYPT)));
    ChainedAsyncRead(std::make_shared<SessionBundle>(std::move(p_server_socket),
      std::move(p_client_socket), std::make_unique<Processor_AES_CFB128>(
        cfg.key_str, *p_seed, AES_DECRYPT)));
  }
  else {
    LogError("Failed to receive ivec seed",
      p_server_socket->remote_endpoint(), err);
  }
}

}  // anonymous namespace

void StartInitProcedure(socket_ptr p_client_socket, socket_ptr p_server_socket,
 const ProcessorConfig& cfg) {
  using namespace std::placeholders;
  auto p_seed = std::make_shared<std::uint32_t>();
  auto buffer = boost::asio::buffer(p_seed.get(), 4);
  auto& server_socket = *p_server_socket;
  boost::asio::async_read(server_socket, std::move(buffer),
    std::bind(&OnIvecSeedRead, std::move(p_client_socket),
      std::move(p_server_socket), std::ref(cfg), std::move(p_seed), _1, _2));
}
