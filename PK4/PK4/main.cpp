#include <SFML/Graphics.hpp>
#include <windows.h>
#include <string>
#include <iostream>
#include <tchar.h>

#include "MainMenu.h"
#include "ApplicationControl.h"

#define BUFSIZE MAX_PATH

const std::string WINDOW_CAPTION = "PK4";

	TCHAR buffer[BUFSIZE];
std::string ExePath()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}
int main()
{
	DWORD dwRet;

	std::cout << ExePath() << std::endl;
	SetCurrentDirectory(ExePath().c_str());

	ApplicationControl applicationControl;
	applicationControl.Run();

	return 0;
}