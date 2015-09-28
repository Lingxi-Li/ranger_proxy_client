// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#pragma once

#include "common.hpp"

#define COPYRIGHT_NOTICE \
  "ranger_proxy_client - Portable client software written in C++14 for\n" \
  "ranger_proxy (https://github.com/ufownl/ranger_proxy).\n\n" \
  "Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)\n" \
  "Distributed under the BSD 3-Clause License.\n" \
  "See accompanying file LICENSE at the root directory of this distribution."

#define CONFIG         "config.txt"
#define LOCAL_PORT     "local_port"
#define REMOTE_HOST    "remote_host"
#define REMOTE_SERVICE "remote_service"
#define KEY_STRING     "key_string"
#define COMPRESS       "compress"
#define ON             "on"
#define OFF            "off"

#define PARA_END "\n" << std::endl
#define RULE_70 \
  "----------------------------------------------------------------------"

// String literal version of __LINE__.
#define LINE LINE_(__LINE__)
#  define LINE_(line) LINE__(line)
#  define LINE__(line) #line
#define FILE_LINE __FILE__ ", " LINE

#define ERROR_MESSAGE(...) __VA_ARGS__ ". " FILE_LINE

#define ERR_MSG_MISSING_EQUAL_SIGN ERROR_MESSAGE("Missing \"=\" in " CONFIG)
#define ERR_MSG_UNKNOWN_ITEM(...)  ERROR_MESSAGE("Unknown item \"" + (__VA_ARGS__) + "\" in " CONFIG)
#define ERR_MSG_CANNOT_OPEN_CONFIG ERROR_MESSAGE("Cannot open " CONFIG)
#define ERR_MSG_EMPTY_CONFIG       ERROR_MESSAGE("Empty " CONFIG)
#define ERR_MSG_LOCAL_PORT_MUST_COME_FIRST ERROR_MESSAGE(LOCAL_PORT " must come first")
#define ERR_MSG_NO_RESOLVED_SERVER ERROR_MESSAGE("No resolved server")

#define GUARD_EXCEPTION_BEGIN try {
#define GUARD_EXCEPTION_END \
  } \
  catch(const std::exception& e) { \
    std::cout << "Exception caught at " FILE_LINE "\n" \
              << e.what() << std::endl; \
  } \
  catch(...) { \
    std::cout << "Unknown exception caught at " FILE_LINE << std::endl; \
  }
