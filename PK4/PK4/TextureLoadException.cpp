#include "TextureLoadException.h"

const char * TextureLoadException::what() const throw()
{
	return (EX_MESSAGE + error_source).c_str();
}

TextureLoadException::TextureLoadException(std::string _error_source) : error_source(_error_source)
{
}

TextureLoadException::~TextureLoadException()
{
}
