#pragma once
#include <exception>
#include <string>
#include <string.h>

class TextureLoadException : public std::exception
{
	const std::string EX_MESSAGE = "Couldn't open texture file: ";
	char * error_message;

public:
	virtual const char * what() const override;

	TextureLoadException(std::string _error_source);
	~TextureLoadException();
};

