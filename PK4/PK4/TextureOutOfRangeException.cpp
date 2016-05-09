#include "TextureOutOfRangeException.h"



TextureOutOfRangeException::TextureOutOfRangeException(std::string _error_source, int _error_index)
{
	error_source = _error_source;
	error_index = _error_index;
}


const char * TextureOutOfRangeException::what() const throw()
{
	return (EX_MESSAGE_1 + std::to_string(error_index) + EX_MESSAGE_2 + error_source);
}

TextureOutOfRangeException::~TextureOutOfRangeException()
{
}
