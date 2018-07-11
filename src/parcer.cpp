#include "../inc/compress.hpp"



int parcer(char *buf, size_t len, socket_ptr sock)
{
    int paylen;
    unsigned char c;


    if (len < 8) {
        boost::asio::write(*sock, boost::asio::buffer("Incorrect message length\n", 25));
        return 1;
    }
    if (buf[0] != 0x53 || buf[1] != 0x54 || buf[2] != 0x52 || buf[3] != 0x59) {
        boost::asio::write(*sock, boost::asio::buffer("Incorrect magic value\n", 22));
        return 1;
    }
    paylen = buf[4] / 16 * 16 * 16 * 16 + buf[4] % 16 * 16 * 16 + buf[5];
//    cout << "\n" << paylen << endl;
    if (buf[7] < 0x01 || buf[7] > 0x04 || buf[6] != 0x00) {
        char response[4];
        response[0] = response[1] = response[2] = 0x00;
        response[3] = 0x03;
        boost::asio::write(*sock, boost::asio::buffer(response, 4));
        return 1;
    }

    if ((buf[7] == 0x01 || buf[7] == 0x03) && paylen == 0 && len == 8)
    {
        char response[4];
        response[0] = response[1] = response[2] = response[3] = 0x00;
        boost::asio::write(*sock, boost::asio::buffer(response, 4));

    }
    if ((buf[7] > 0x00 && buf[7] < 0x04 && paylen != 0) || len != paylen + 8) {
        char response[4];
        response[0] = response[1] = response[2] = 0x00;
        response[3] = 0x02;
        boost::asio::write(*sock, boost::asio::buffer(response, 4));
    }

    return 0;
}
