// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#include "processor_config.hpp"

#include "macro_def.hpp"

void ProcessorConfig::ParseConfigItem(const std::string& key,
 const std::string& value) {
  key == KEY_STRING ? (void)(key_str  = value) :
  key == COMPRESS   ? (void)(compress = value == ON) :
                      throw std::invalid_argument(ERR_MSG_UNKNOWN_ITEM(key));
}

void Print(const ProcessorConfig& cfg) {
  std::cout << KEY_STRING ": " << cfg.key_str << "\n" COMPRESS ": "
            << cfg.compress << std::endl;
}
