#pragma once
#include <exception>
#include <string>

class TextureOutOfRangeException :
	public std::exception
{
private:
	const std::string EX_MESSAGE_1 = "No index ";
	const std::string EX_MESSAGE_2 = " in ";

	int error_index;
	std::string error_source;

public:
	const char * what() const throw();

	TextureOutOfRangeException(std::string _error_source, int _error_index);
	~TextureOutOfRangeException();
};

