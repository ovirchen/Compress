
#include "Server.hpp"
#include <stdlib.h>

Server::Server() {
    _tbs = _tbr = _after_comp = _before_comp = 0;
}
Server::~Server() { }

int Server::ping(int paylen, socket_ptr sock)
{
    boost::unique_lock<boost::mutex> locker(mtx, boost::defer_lock);
    char *response = create_response(8);

    cout << "ping" << endl;

    if (paylen != 0) {
        response[7] = 0x23; // 35 - Incorrect payload length
        boost::asio::write(*sock, boost::asio::buffer(response, 8));
		delete response;
        locker.lock();
        _tbs += 8;
        locker.unlock();
        throw ServerException("incorrect payload length");
    }
    boost::asio::write(*sock, boost::asio::buffer(response, 8));
	delete response;
    locker.lock();
    _tbs += 8;
    locker.unlock();
    return 0;
}

int Server::get_stat(int paylen, socket_ptr sock)
{
    boost::unique_lock<boost::mutex> locker(mtx, boost::defer_lock);
	char *response = create_response(13);

    cout << "stat" << endl;

    if (paylen != 0) {
        response[7] = 0x23; // 35 - Incorrect payload length
        boost::asio::write(*sock, boost::asio::buffer(response, 8));
		delete response;
        locker.lock();
        _tbs += 8;
        locker.unlock();
        throw ServerException("incorrect payload length");
    }
    unsigned char *byte = (unsigned char*)&_tbr;
    for (int i = 0; i < 4; i++) {
        response[4 + i] = byte[i];
    }
    byte = (unsigned char*)&_tbs;
    for (int i = 0; i < 4; i++) {
        response[8 + i] = byte[i];
    }
    if (_before_comp != 0)
    {
        string buf = to_string(_after_comp * 100 / _before_comp);
        response[12] = (unsigned char)strtol(buf.c_str(), NULL, 16);
    }
    boost::asio::write(*sock, boost::asio::buffer(response, 13));
	delete response;
    locker.lock();
    _tbs += 13;
    locker.unlock();
    return 0;
}

int Server::reset_stat(int paylen, socket_ptr sock)
{
    boost::unique_lock<boost::mutex> locker(mtx, boost::defer_lock);
	char *response = create_response(8);

    cout << "reset" << endl;

    if (paylen != 0) {
        response[7] = 0x23; // 35 - Incorrect payload length
        boost::asio::write(*sock, boost::asio::buffer(response, 8));
		delete response;
        locker.lock();
        _tbs += 8;
        locker.unlock();
        throw ServerException("incorrect payload length");
    }
    locker.lock();
    _tbr = 0;
    _tbs = 0;
    _before_comp = 0;
    _after_comp = 0;
    locker.unlock();
    boost::asio::write(*sock, boost::asio::buffer(response, 8));
	delete response;
    locker.lock();
    _tbs += 4;
    locker.unlock();
    return 0;
}
int Server::check_invalid_char(char *buf, size_t len, int paylen, socket_ptr sock)
{
	boost::unique_lock<boost::mutex> locker(mtx, boost::defer_lock);
	char *response = create_response(8);

	if (len < paylen + 8)
	{
		response[7] = 0x21; // 33 - Incorrect message length
		boost::asio::write(*sock, boost::asio::buffer(response, 8));
		delete response;
		locker.lock();
		_tbs += 8;
		locker.unlock();
		throw ServerException("incorrect message length");
	}
	int i = 7;
	while (++i < paylen + 8)
	{
		if (buf[i] < 97 || buf[i] > 122)
		{
			if (buf[i] >= 65 && buf [i] <= 90) {
				response[7] = 0x24; // 36 - <invalid: contains uppercase characters>
			}
			else if (buf[i] >= 48 && buf [i] <= 57) {
				response[7] = 0x25; // 37 - <invalid: contains numbers>
			}
			else {
				response[7] = 0x26; // 38 - <invalid: contains other characters>
			}
			boost::asio::write(*sock, boost::asio::buffer(response, 8));
			delete response;
			locker.lock();
			_tbs += 8;
			locker.unlock();
			if (buf[i] >= 65 && buf [i] <= 90) {
				throw ServerException("<invalid: contains uppercase characters>");
			}
			else if (buf[i] >= 48 && buf [i] <= 57) {
				throw ServerException("<invalid: contains numbers>");
			}
			else {
				throw ServerException("<invalid: contains other characters>");
			}
		}
	}
	return 0;
}

int Server::compress(char *buf, size_t len, int paylen, socket_ptr sock)
{
	cout << "compress" << endl;

	check_invalid_char(buf, len, paylen, sock);

	boost::unique_lock<boost::mutex> locker(mtx, boost::defer_lock);
	char *response = create_response(paylen + 6);
	int i = 7;
	int num = 0;
	int resp = 6;
	char c = buf[8];
	while (++i < paylen + 8)
	{
		if (buf[i] == c)
		{
			num++;
		}
		else
		{
			if (num > 2) {
				string numstr = to_string(num);
				for (int j = 0; j < strlen(numstr.c_str()); j++) {
					response[resp++] = numstr[j];
				}
			}
			else if (num == 2)
			{
				response[resp++] = c;
			}
			response[resp++] = c;
			num = 1;
			c = buf[i];
		}
	}
	i = (int)strlen(response) - 6;
	response[4] = i / 16 + 48;
	response[5] = i % 16 + 48;
	boost::asio::write(*sock, boost::asio::buffer(response, i + 6));
	delete response;
	locker.lock();
	_tbs += i + 6;
	locker.unlock();
	return 0;
}

int Server::check_magic(char *buf, size_t len, socket_ptr sock)
{
	boost::unique_lock<boost::mutex> locker(mtx, boost::defer_lock);
	char *response = create_response(8);

	if (len < 8) {
		response[7] = 0x21; // 33 - Incorrect message length
		boost::asio::write(*sock, boost::asio::buffer(response, 8));
		delete response;
		locker.lock();
		_tbs += 8;
		locker.unlock();
		throw ServerException("incorrect message length");
	}
	if (buf[0] != 0x53 || buf[1] != 0x54 || buf[2] != 0x52 || buf[3] != 0x59) {
		response[7] = 0x22; // 34 - Incorrect magic value
		boost::asio::write(*sock, boost::asio::buffer(response, 8));
		delete response;
		locker.lock();
		_tbs += 8;
		locker.unlock();
		throw ServerException("incorrect magic value");
	}
	delete response;
	return 0;
}

int Server::handler(char *buf, size_t len, socket_ptr sock)
{
    boost::unique_lock<boost::mutex> locker(mtx, boost::defer_lock);
	char *response = create_response(8);

	try {
        locker.lock();
        _tbr += (unsigned long int) len;
        locker.unlock();
		check_magic(buf, len, sock);
        int paylen = buf[4] / 16 * 16 * 16 * 16 + buf[4] % 16 * 16 * 16 + buf[5];
        if (paylen > 4096) {
            response[7] = 0x02;
            boost::asio::write(*sock, boost::asio::buffer(response, 8));
            locker.lock();
            _tbs += 8;
            locker.unlock();
            throw ServerException("message too large");
        }
        if (buf[7] < 0x01 || buf[7] > 0x04 || buf[6] != 0x00) {
            response[7] = 0x03;
            boost::asio::write(*sock, boost::asio::buffer(response, 8));
            locker.lock();
            _tbs += 8;
            locker.unlock();
            throw ServerException("unsupported request type");
        }
        if (buf[7] == 0x01)
            ping(paylen, sock);
        if (buf[7] == 0x02)
            get_stat(paylen, sock);
        if (buf[7] == 0x03)
            reset_stat(paylen, sock);
		if (buf[7] == 0x04)
			compress(buf, len, paylen, sock);
    }
    catch (exception &e)
    {
        std::cerr << "Exception in handler: " << e.what() << endl;
    }
	delete response;
    return 0;
}

Server::ServerException::ServerException(const string& message) : message_(message) { }
Server::ServerException::~ServerException() { }