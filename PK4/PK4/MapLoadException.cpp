#include "MapLoadException.h"


MapLoadException::MapLoadException(std::string & message)
{
	size = message.length() + 1;
	c_message = new char[size];
	strcpy_s(c_message, size, message.c_str());
}


const char * MapLoadException::what() const
{
	return c_message;
}

MapLoadException::~MapLoadException()
{
	if (c_message != nullptr)
		delete[size] c_message;
}
