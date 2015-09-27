// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#include "processor_aes_cfb128.hpp"

Processor_AES_CFB128::Processor_AES_CFB128(std::string key_str,
 std::uint32_t seed, int type)
 : type_(type) {
  auto key_len = key_str.size() <= 16 ? 16 :
                 key_str.size() <= 24 ? 24 : 
                                        32 ;
  key_str.resize(key_len);
  AES_set_encrypt_key(reinterpret_cast<const byte*>(key_str.data()),
    key_len * 8, &key_);
  std::minstd_rand rand(seed);
  for (byte* p = ivec_.data(); p < ivec_.data() + 16; p += 4) {
    auto val = rand();
    std::memcpy(p, &val, 4);
  }
}

byte_vector_ptr Processor_AES_CFB128::ProcessData(const byte* p_data,
 std::size_t size) {
  auto p_vec = std::make_shared<byte_vector>(size);
  AES_cfb128_encrypt(p_data, p_vec->data(), size, &key_, ivec_.data(), &num_,
    type_);
  return p_vec;
}
