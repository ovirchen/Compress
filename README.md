# Compress
Target platform - Ubuntu 18.04
Language - C++
Compiler - GCC 7.3.0
Using - Boost C++ Libraries

	This project represents multi-threaded synchronous TCP server using a 4000 port.

	Every thread is created, reads and treats the request separately using function "session" in "main.cpp".

	In file "Server.hpp" there is a description of class Server. There are definitions of functions, constructors and
destructors in file "Server.cpp". The class checks received requests and sents responses. Also it has own exception
class to describe errors in server's standard output stream. The private variables _tbr,_tbs is respectively Total Bytes
Received and Total Bytes Sent. Another two take part in calculation of Compression Ratio in function "get_stat".
Function "reset_stat" sets all of these variables to zero, but after response to this action _tbs isn`t zero anymore. So
you will never get stats response with only zeros. To prevent synchronous access to the variables I used mutex.

	The server defined 4KiB as the maximum payload size, so the BUFFER_SIZE for reading request is 4097: when 4097 -
this is an error, otherwise everything is ok.

	I use Boost library because it`s one of the best by description on the Internet.

Additional errors:
Status Code  -   Meaning
  33 - Incorrect message length
  34 - Incorrect magic value
  35 - Incorrect payload length
  36 - <invalid: contains uppercase characters>
  37 - <invalid: contains numbers>
  38 - <invalid: contains other characters>
