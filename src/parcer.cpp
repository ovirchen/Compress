#include "../inc/compress.hpp"

int parcer(char *buf, size_t len, socket_ptr sock)
{
    int paylen;
    int reqcode;

    if (len < 14) {
        boost::asio::write(*sock, boost::asio::buffer("Incorrect message length\n", 25));
        return 1;
    }
    if (atoi(buf) != 5354 || atoi(buf + 4) != 5259) {
        boost::asio::write(*sock, boost::asio::buffer("Incorrect magic value\n", 22));
        return 2;
    }
    paylen = atoi(buf + 9);
    if ((reqcode = atoi(buf + 14)) < 1 || reqcode > 4) {
        boost::asio::write(*sock, boost::asio::buffer("Incorrect request code\n", 23));
        return 3;
    }
    return 0;
}