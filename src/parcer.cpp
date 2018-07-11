#include "../inc/compress.hpp"

int parcer(char *buf, size_t len, socket_ptr sock)
{
    int paylen;
    int reqcode;
    unsigned char c;


    if (len < 8) {
        boost::asio::write(*sock, boost::asio::buffer("Incorrect message length\n", 25));
        return 1;
    }
    cout << buf[0] << endl;
    if (buf[0] != 0x53 || buf[1] != 0x54 || buf[2] != 0x52 || buf[3] != 0x59) {
        boost::asio::write(*sock, boost::asio::buffer("Incorrect magic value\n", 22));
        return 2;
    }
//    paylen = buf[4];
    if (buf[7] < 0x01 || buf[7] > 0x04) {
        boost::asio::write(*sock, boost::asio::buffer("Incorrect request code\n", 23));
        return 3;
    }
    return 0;
}
