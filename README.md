# Compress
Target platform - Ubuntu 18.04
Language - C++
Compiler - GCC 7.3.0
Using - Boost C++ Libraries

  In this code released multi-threaded synchronous server. File Server.hpp has description of class Server, that do all the
work with received requests and sents all the responses. Also it has its own exception class, that descride error code in
server's standard output stream for errors. Release of all Server's functions is in file called Server.cpp. Variables _tbr,
_tbs is respectively Total Bytes Received and Total Bytes Sent. Another two consider in Compression Ratio. Function reset_stat
is set all of these variables to zero, but after response of the action _tbs is not zero anymore. So you will never get
stats response with only zeros. I used mutex for temporarily locking changing these variables.

I used Boost library because by description in the Internet this is one of the best.

ADDITIONAL ERRORS
Status Code  -   Meaning
  33 - Incorrect message length
  34 - Incorrect magic value
  35 - Incorrect payload length
  36 - <invalid: contains uppercase characters>
  37 - <invalid: contains numbers>
  38 - <invalid: contains other characters>
