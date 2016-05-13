#include "TextureLoadException.h"

const char * TextureLoadException::what() const
{
	return error_message;
}

TextureLoadException::TextureLoadException(std::string _error_source)
{
	std::string sub_message = EX_MESSAGE + _error_source;
	int length = sub_message.length() + 1;
	error_message = new char[length];
	strcpy_s(error_message, length, sub_message.c_str());
}

TextureLoadException::~TextureLoadException()
{
	if (error_message != NULL)
		delete[] error_message;
}
