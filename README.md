# ranger_proxy_client

<a name="toc"></a>
Table of contents:

* [Introduction](#intro)
* [Requirements](#require)
* [Distribution Structure](#struct)
* [Build Instructions](#build)
* [License](#license)

<a name="intro"></a>
## Introduction

**ranger_proxy_client** implements a client for [ranger_proxy](https://github.com/ufownl/ranger_proxy) which implements a [SOCKS5](https://www.ietf.org/rfc/rfc1928.txt)-based proxy server. The server builds another layer between SOCKS5 and TCP to support [AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) encryption and optional data compression. As a result, vanilla SOCKS5 applications like Google Chrome cannot use it directly. ranger_proxy_client comes in as a client to the remote ranger_proxy server and as a local SOCKS5 server to the applications. It handles the intricacies of the added layer in communicating with the remote server on behalf of local applications. The gap between the remote server and local applications is thus bridged. Take Chrome for example. If the local server is configured to listen on port `56789`, then you can launch Chrome with the parameter `--proxy-server="SOCKS5://127.0.0.1:56789"` to use the proxy service.

It should be noted that although ranger_proxy supports optional data compression, the functionality is not implemented in this client software. We think deciding whether and how data compression should be done is a responsibility of the applications rather than the client. The client may support various applications, and it is difficult to perform data compression that is generally useful. Besides, the stream-oriented nature of the client is in conflict with the block-oriented nature of data compression. Nevertheless, the interface for data compression is built, and it would be easy to integrate an implementation if you choose.

<a name="require"></a>
## Requirements

* Build tools supporting C++14 (VC15 tested)
* [Boost C++ Libraries](http://www.boost.org) (v1.58.0 tested)
* [OpenSSL Toolkit](https://www.openssl.org) (v1.0.2d tested)
* On Windows platforms, Vista/2008 or above is required (see the *Remarks* section [here](http://www.boost.org/doc/libs/1_59_0/doc/html/boost_asio/reference/basic_stream_socket/cancel/overload1.html))
* [CMake](https://cmake.org) 3.0 is required to process the listfile

<a name="struct"></a>
## Distribution Structure

	/....................................Root directory
	    LICENSE
	    README.md........................The file you are reading now
	    CMakeLists.txt...................CMake listfile
	    config.txt.......................Config file for the client 
	    src/.............................All source files of the project

<a name="build"></a>
## Build Instructions

Simply speaking, compile all source files and link with Boost and OpenSSL. A CMake listfile is provided. It has been tested on both Windows and Linux platforms.


<a name="license"></a>
## License

This software is distributed under the [BSD 3-Clause License](http://opensource.org/licenses/BSD-3-Clause). See accompanying `LICENSE` file at the root directory of this distribution.
