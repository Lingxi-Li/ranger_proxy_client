cmake_minimum_required(VERSION 3.0)
project(ranger_proxy_client)

set(CMAKE_CONFIGURATION_TYPES Release CACHE STRING "[ Release | Debug | RelWithDebInfo | MinSizeRel ]" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(boost_include_dir "" CACHE PATH "Path to Boost include directory")
set(boost_system_shared_lib_file "" CACHE FILE "Path to Boost system shared library file")
add_library(boost_shared_lib INTERFACE)
target_include_directories(boost_shared_lib SYSTEM INTERFACE ${boost_include_dir})
target_compile_definitions(boost_shared_lib INTERFACE BOOST_ALL_NO_LIB BOOST_ALL_DYN_LINK)
target_link_libraries(boost_shared_lib INTERFACE ${boost_system_shared_lib_file})

set(openssl_include_dir "" CACHE PATH "Path to OpenSSL include directory")
set(openssl_crypto_shared_lib_file "" CACHE FILE "Path to OpenSSL crypto shared library file")
add_library(openssl_shared_lib INTERFACE)
target_include_directories(openssl_shared_lib SYSTEM INTERFACE ${openssl_include_dir})
target_link_libraries(openssl_shared_lib INTERFACE ${openssl_crypto_shared_lib_file})

set(headers
  src/client_acceptor.hpp
  src/common.hpp
  src/computing_service.hpp
  src/config.hpp
  src/initiator.hpp
  src/macro_def.hpp
  src/network_io_service.hpp
  src/processor.hpp
  src/processor_aes_cfb128.hpp
  src/processor_config.hpp
  src/server_config.hpp
  src/server_connector.hpp
  src/session.hpp
  src/singleton.hpp
  src/util.hpp)
set(sources
  src/client_acceptor.cpp
  src/config.cpp
  src/initiator.cpp
  src/main.cpp
  src/processor_aes_cfb128.cpp
  src/processor_config.cpp
  src/server_config.cpp
  src/server_connector.cpp
  src/session.cpp
  src/util.cpp)
add_executable(ranger_proxy_client ${headers} ${sources})
target_compile_definitions(ranger_proxy_client PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:_WIN32_WINNT=0x0600 _CRT_SECURE_NO_WARNINGS>)
target_compile_options(ranger_proxy_client PRIVATE 
  $<$<CXX_COMPILER_ID:MSVC>:/wd4005>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-std=c++14>)
target_link_libraries(ranger_proxy_client PRIVATE
  boost_shared_lib openssl_shared_lib
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-pthread>)

install(TARGETS ranger_proxy_client
  RUNTIME DESTINATION bin)
install(FILES config.txt DESTINATION bin)
