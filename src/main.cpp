#include "compress.hpp"
#include "Server.hpp"

void session(socket_ptr sock, Server &serv)
{
	try
	{
		while (1)
		{
			vector<char> buf(BUFFER_SIZE);

			boost::system::error_code error;
			size_t length = sock->read_some(boost::asio::buffer(buf), error);
			if (error == boost::asio::error::eof)
			{
				break; // Connection closed cleanly.
			}
			else if (error)
			{
				throw boost::system::system_error(error); // Some other error.
			}
			serv.handler(buf.data(), length, sock);
		}
	}
	catch (std::exception &e)
	{
		cerr << "Exception in thread: " << e.what() << endl;
	}
}

int main(int ac, char **av)
{
	try
	{
		if (ac != 2)
		{
			cerr << "Usage: ./compress <port>\n";
			return 1;
		}
		boost::asio::io_service service;
		tcp::endpoint ep(tcp::v4(), atoi(av[1]));
		tcp::acceptor ac(service, ep);
		Server serv;
		while (1)
		{
			socket_ptr sock(new tcp::socket(service));
			ac.accept(*sock);
			boost::thread thrd(boost::bind(session, sock, boost::ref(serv)));
		}
	}
	catch (exception &e)
	{
		cerr << "Exception: " << e.what() << endl;
	}
	return 0;
}
