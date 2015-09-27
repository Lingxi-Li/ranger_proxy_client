// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#pragma once

#include "common.hpp"

class Processor {
public:
  virtual ~Processor() = default;
  virtual byte_vector_ptr ProcessData(const byte* p_data, std::size_t size) = 0;
};

using processor_ptr = std::shared_ptr<Processor>;
using unique_processor_ptr = std::unique_ptr<Processor>;
