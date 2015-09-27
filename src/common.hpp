// ranger_proxy_client - Portable client software written in C++14 for
// ranger_proxy (https://github.com/ufownl/ranger_proxy).
//
// Copyright (C) 2015 Li, Lingxi (lilingxi.cs@gmail.com, 908931294@qq.com)
// Distributed under the BSD 3-Clause License.
// See accompanying file LICENSE at the root directory of this distribution.
//
#pragma once

#include <cinttypes>
#include <cstddef>
#include <cstring>
#include <ctime>

#include <array>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>

#include <boost/asio.hpp>

using byte = unsigned char;
using byte_vector = std::vector<byte>;
using byte_vector_ptr = std::shared_ptr<byte_vector>;
using read_buffer = std::array<byte, 128 * 1024>;
using read_buffer_ptr = std::shared_ptr<read_buffer>;
using tcp = boost::asio::ip::tcp;
using socket_ptr = std::shared_ptr<tcp::socket>;
using socket_ptr_pair = std::pair<socket_ptr, socket_ptr>;
using error_code = boost::system::error_code;
