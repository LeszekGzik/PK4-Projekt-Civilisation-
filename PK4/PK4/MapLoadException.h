#pragma once
#include "vcruntime_exception.h"
#include <string>
#include <string.h>

class MapLoadException :
	public std::exception
{
private:
	char * c_message = nullptr;
	size_t size;

public:
	virtual const char * what() const override;

	MapLoadException(std::string & message);
	~MapLoadException();
};

