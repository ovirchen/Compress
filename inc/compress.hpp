#ifndef COMPRESS_H
#define COMPRESS_H

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#define BUFFER_SIZE 1024

using namespace std;
using boost::asio::ip::tcp;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

int parcer(char *buf, size_t len, socket_ptr sock);

#endif
