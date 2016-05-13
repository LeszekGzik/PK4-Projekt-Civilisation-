#pragma once
#include <exception>
#include <string>
#include <string.h>

class TextureOutOfRangeException :
	public std::exception
{
private:
	const std::string EX_MESSAGE_1 = "No index ";
	const std::string EX_MESSAGE_2 = " in ";

	int error_index;
	char * error_message;

public:
	virtual const char * what() const override;

	TextureOutOfRangeException(std::string _error_source, int _error_index);
	~TextureOutOfRangeException();
};

