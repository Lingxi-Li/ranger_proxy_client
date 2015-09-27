// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#pragma once

#include <openssl/aes.h>

#include "processor.hpp"

class Processor_AES_CFB128
 : public Processor {
public:
  using ivec_t = std::array<byte, 16>;

  // type = AES_ENCRYPT or AES_DECRYPT.
  Processor_AES_CFB128(std::string key_str, std::uint32_t seed, int type);
  virtual byte_vector_ptr ProcessData(const byte* p_data, std::size_t size);

private:
  AES_KEY key_ = {};
  ivec_t ivec_ = {};
  int num_ = 0;
  int type_;
};
