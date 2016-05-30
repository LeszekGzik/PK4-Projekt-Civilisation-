#include "IndexOutOfRangeException.h"



IndexOutOfRangeException::IndexOutOfRangeException(std::string _error_source, int _error_index)
{
	error_index = _error_index;
	std::string sub_error = EX_MESSAGE_1 + std::to_string(_error_index) + EX_MESSAGE_2 + _error_source;
	int length = sub_error.length() + 1;
	error_message = new char[length];
	strcpy_s(error_message, length, sub_error.c_str());
}


const char * IndexOutOfRangeException::what() const
{
	return error_message;
}

IndexOutOfRangeException::~IndexOutOfRangeException()
{
	if (error_message != NULL)
		delete[] error_message;	
}
