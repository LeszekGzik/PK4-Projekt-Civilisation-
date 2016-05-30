#pragma once
#include <exception>
#include <string>
#include <string.h>

class FileLoadException : public std::exception
{
	const std::string EX_MESSAGE = "Couldn't open file: ";
	char * error_message;

public:
	virtual const char * what() const override;

	FileLoadException(std::string _error_source);
	~FileLoadException();
};

