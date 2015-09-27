// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#include "session.hpp"

#include "computing_service.hpp"
#include "network_io_service.hpp"
#include "util.hpp"

namespace {

void ChainedAsyncWrite(session_bundle_ptr p_bundle, byte_vector_ptr p_vec);

void DataProcessingTask(session_bundle_ptr p_bundle, std::size_t size) {
  auto p_vec = p_bundle->p_processor->ProcessData(
    p_bundle->r_buffer.data(), size);
  if (p_vec->size()) {
    NetworkIoService::Get().post(std::bind(&ChainedAsyncWrite,
      std::move(p_bundle), std::move(p_vec)));
  }
  else {
    NetworkIoService::Get().post(std::bind(&ChainedAsyncRead,
      std::move(p_bundle)));
  }
}

void OnDataRead(session_bundle_ptr p_bundle, const error_code& err,
 std::size_t size) {
  if (size) {
    ComputingService::Get().post(std::bind(&DataProcessingTask,
      std::move(p_bundle), size));
  }
  else {
    if (!err) {
      ChainedAsyncRead(std::move(p_bundle));
    }
    else {
      error_code err;
      p_bundle->p_write_socket->shutdown(tcp::socket::shutdown_receive, err);
      p_bundle->p_write_socket->cancel(err);
    }
  }
}

void OnDataWritten(session_bundle_ptr p_bundle, byte_vector_ptr p_vec,
 const error_code& err, std::size_t size_written) {
  if (size_written == p_vec->size()) {
    ChainedAsyncRead(std::move(p_bundle));
  }
  else {
    if (err == boost::asio::error::operation_aborted) {
      p_vec->erase(p_vec->begin(), p_vec->begin() + size_written);
      ChainedAsyncWrite(std::move(p_bundle), std::move(p_vec));
    }
    else {
      LogError("Failed to write",
        p_bundle->p_write_socket->remote_endpoint(), err);
      ChainedAsyncRead(std::move(p_bundle));
    }
  }
}

void ChainedAsyncWrite(session_bundle_ptr p_bundle, byte_vector_ptr p_vec) {
  using namespace std::placeholders;
  auto buffer = boost::asio::buffer(*p_vec);
  auto& write_socket = *p_bundle->p_write_socket;
  boost::asio::async_write(write_socket, std::move(buffer),
    std::bind(&OnDataWritten, std::move(p_bundle), std::move(p_vec), _1, _2));
}

}  // anonymous namespace

SessionBundle::SessionBundle(const socket_ptr& p_read_socket,
 const socket_ptr& p_write_socket, unique_processor_ptr&& p_processor)
 : p_read_socket(p_read_socket)
 , p_write_socket(p_write_socket)
 , p_processor(std::move(p_processor)) {}

SessionBundle::SessionBundle(socket_ptr&& p_read_socket,
 socket_ptr&& p_write_socket, unique_processor_ptr&& p_processor)
 : p_read_socket(std::move(p_read_socket))
 , p_write_socket(std::move(p_write_socket))
 , p_processor(std::move(p_processor)) {}

void ChainedAsyncRead(session_bundle_ptr p_bundle) {
  using namespace std::placeholders;
  auto buffer = boost::asio::buffer(p_bundle->r_buffer.data(),
    p_bundle->r_buffer.size());
  auto& read_socket = *p_bundle->p_read_socket;
  read_socket.async_read_some(buffer, std::bind(&OnDataRead,
    std::move(p_bundle), _1, _2));
}
