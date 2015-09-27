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

**ranger_proxy_client** is a client for [ranger_proxy](https://github.com/ufownl/ranger_proxy) which implements a [SOCKS5](https://www.ietf.org/rfc/rfc1928.txt)-based proxy server. The server builds another layer between SOCKS5 and TCP to support [AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) encryption and optional data compression. As a result, vanilla SOCKS5 applications like Google Chrome cannot use it directly. ranger_proxy_client comes in as a client to the remote ranger_proxy server and as a local SOCKS5 server to the applications. It handles the intricacies of the added layer in communicating with the remote server on behalf of local applications. The gap between the remote server and local applications is thus bridged. Take Chrome for example. If the local server is configured to listen on port `56789`, then you can launch Chrome with the parameter `--proxy-server="SOCKS5://127.0.0.1:56789"` or `--proxy-server="SOCKS5://[::1]:56789"` to use the proxy service.

It should be noted that although ranger_proxy supports optional data compression, the functionality is not implemented in this client software. We think deciding whether and how data compression should be done is a responsibility of the applications rather than the client. The client may support various applications, and it is difficult to perform data compression that is generally useful. Besides, the stream-oriented nature of the client is in conflict with the block-oriented nature of data compression. Nevertheless, the interface for data compression is built, and it would be easy to integrate an implementation if you choose.

<a name="require"></a>
## Requirements

* Build tools supporting C++14
* [Boost C++ Libraries](http://www.boost.org)
* [OpenSSL Toolkit](https://www.openssl.org)

<a name="struct"></a>
## Distribution Structure

	/....................................Root directory
	    LICENSE
	    README.md........................The file you are reading now
	    src/.............................All source files of this project
	    vc15/............................A VC15 configuration
	        bin/.........................Output and working directory
	            config.txt...............Config file for the client
	        boost/
	            boost/...................Put Boost headers here
				import_lib/..............Put Boost import libraries here
			openssl/.....................The same for OpenSSL
			ranger_proxy_client/.........VC15 files

**Remainder:** Config file for the client is found at `/vc15/bin/config.txt`.

<a name="build"></a>
## Build Instructions

Simply speaking, compile all source files and link with Boost and OpenSSL. For convenience, a Visual C++ 2015 (VC15) configuration is included in the distribution with the following options:

* Release build for x86
* Dynamically link to C/C++ runtime library
* Dynamically link to Boost by defining the macro `BOOST_ALL_DYN_LINK`
* Support Windows Vista/2008 and later by defining `_WIN32_WINNT` to `0x0600`. See the _Remarks_ section [here](http://www.boost.org/doc/libs/1_59_0/doc/html/boost_asio/reference/basic_stream_socket/cancel/overload1.html).

<a name="license"></a>
## License

This software is distributed under the [BSD 3-Clause License](http://opensource.org/licenses/BSD-3-Clause). See accompanying file `LICENSE` at the root directory of this distribution.
