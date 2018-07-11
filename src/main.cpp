#include "../inc/compress.hpp"

void session(socket_ptr sock)
{
	try
	{
		while (1)
		{
			char buf[BUFFER_SIZE];

			boost::system::error_code error;
			size_t length = sock->read_some(boost::asio::buffer(buf), error);
			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

//			boost::asio::write(*sock, boost::asio::buffer(buf, length));
            parcer(buf, length, sock);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}

int main(int ac, char** av)
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
		while (1) {
			socket_ptr sock(new tcp::socket(service));
			ac.accept(*sock);
			boost::thread thrd(boost::bind(session, sock));
		}
	}
	catch (exception &e)
	{
		cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
