
#ifndef SERVER_H
#define SERVER_H

#include "compress.hpp"

class Server {
public:
	Server();
	~Server();

	int handler(char *buf, size_t len, socket_ptr sock);

	class ServerException : public exception {
	public:
		ServerException(const string &message);
		~ServerException();
		virtual const char *what() const throw() {
			return message_.c_str();
		}

	private:
		string message_;
	};

private:
	boost::mutex mtx;
	unsigned long int _tbs;
	unsigned long int _tbr;
	unsigned long int _before_comp;
	unsigned long int _after_comp;

	char	*create_response(int length);
	int		ping(int paylen, socket_ptr sock);
	int		get_stat(int paylen, socket_ptr sock);
	int		reset_stat(int paylen, socket_ptr sock);
	int		check_invalid_char(char *buf, size_t len, int paylen, socket_ptr sock);
	int		compress(char *buf, size_t len, int paylen, socket_ptr sock);
	int		check_magic(char *buf, size_t len, socket_ptr sock);
};

#endif