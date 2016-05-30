#include <SFML/Graphics.hpp>
#include <windows.h>
#include <string>
#include <iostream>
#include <tchar.h>

#include "MainMenu.h"
#include "ApplicationControl.h"

#define BUFSIZE MAX_PATH

const std::string WINDOW_CAPTION = "PK4";
const std::string EXE_ERR = "Couldn't setup path ";

std::string ExePath()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

int main()
{
	std::string path = ExePath();
	BOOL result = SetCurrentDirectory(path.c_str());

	if (result == FALSE)
	{
		std::cout << EXE_ERR << path << std::endl;
		std::cin.get();
		return 0;
	}

	ApplicationControl applicationControl;
	applicationControl.run();

	return 0;
}