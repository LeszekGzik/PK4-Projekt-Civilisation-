#pragma once
#include <exception>
#include <string>

class TextureLoadException : public std::exception
{
	const std::string EX_MESSAGE = "Couldn't open texture file: ";
	std::string error_source;

public:
	const char * what() const throw();

	TextureLoadException(std::string _error_source);
	~TextureLoadException();
};

