
#include "compress.hpp"

char *create_response(int i)
{
	char *response = new char[i + 1];
	response[i] = '\0';
	memset(response, 0x00, i);
	response[0] = 0x53;
	response[1] = 0x54;
	response[2] = 0x52;
	response[3] = 0x59;
	return response;
}