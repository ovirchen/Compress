#include "../inc/compress.hpp"

static int ping(int paylen, socket_ptr sock)
{
    char response[4];
    memset(response, 0x00, 4);

    cout << "ping" << endl;

    if (paylen == 0)
    {
        boost::asio::write(*sock, boost::asio::buffer(response, 4));
        g_tbs += 4;
        return 0;
    }
    response[3] = 0x23; // 35 - Incorrect payload length
    boost::asio::write(*sock, boost::asio::buffer(response, 4));
    g_tbs += 4;
    return 1;
}

static int get_stat(int paylen, socket_ptr sock)
{
    char response[9];
    memset(response, 0x00, 9);

    cout << "stat" << endl;

    if (paylen != 0) {
        response[3] = 0x23; // 35 - Incorrect payload length
        boost::asio::write(*sock, boost::asio::buffer(response, 4));
        g_tbs += 4;
        return 1;
    }
    unsigned char *byte = (unsigned char*)&g_tbr;
    for (int i = 0; i < 4; i++) {
        response[i] = byte[i];
    }
    byte = (unsigned char*)&g_tbs;
    for (int i = 0; i < 4; i++) {
        response[4 + i] = byte[i];
    }
    if (g_before_comp != 0)
    {
        std::string buf = to_string(g_after_comp * 100 / g_before_comp);
        response[8] = (unsigned char)strtol(buf.c_str(), NULL, 16);
    }
    boost::asio::write(*sock, boost::asio::buffer(response, 9));
    g_tbs += 9;
    return 0;
}

static int reset_stat(int paylen, socket_ptr sock)
{
    char response[4];
    memset(response, 0x00, 4);

    cout << "reset" << endl;

    if (paylen != 0) {
        response[3] = 0x23; // 35 - Incorrect payload length
        boost::asio::write(*sock, boost::asio::buffer(response, 4));
        g_tbs += 4;
        return 1;
    }
    g_tbr = 0;
    g_tbs = 0;
    g_before_comp = 0;
    g_after_comp = 0;
    boost::asio::write(*sock, boost::asio::buffer(response, 4));
    g_tbs += 4;
    return 0;
}

int parcer(char *buf, size_t len, socket_ptr sock)
{
    int     paylen;
    char    response[4];
    memset(response, 0x00, 4);

    g_tbr += (unsigned long int)len;
    if (len < 8) {
        response[3] = 0x21; // 33 - Incorrect message length
        boost::asio::write(*sock, boost::asio::buffer(response, 4));
        g_tbs += 4;
        return 1;
    }
    if (buf[0] != 0x53 || buf[1] != 0x54 || buf[2] != 0x52 || buf[3] != 0x59) {
        response[3] = 0x22; // 34 - Incorrect magic value
        boost::asio::write(*sock, boost::asio::buffer(response, 4));
        g_tbs += 4;
        return 1;
    }
    paylen = buf[4] / 16 * 16 * 16 * 16 + buf[4] % 16 * 16 * 16 + buf[5];
    if (paylen > 4096)
    {
        response[3] = 0x02;
        boost::asio::write(*sock, boost::asio::buffer(response, 4));
        g_tbs += 4;
        return 1;
    }
//    cout << "\n" << paylen << endl;
    if (buf[7] < 0x01 || buf[7] > 0x04 || buf[6] != 0x00) {
        response[3] = 0x03;
        boost::asio::write(*sock, boost::asio::buffer(response, 4));
        g_tbs += 4;
        return 1;
    }
    if (buf[7] == 0x01)
        return ping(paylen, sock);
    if (buf[7] == 0x02)
        return get_stat(paylen, sock);
    if (buf[7] == 0x03)
        return reset_stat(paylen, sock);

    return 0;
}
