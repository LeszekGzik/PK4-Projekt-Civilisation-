#pragma once
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <SFML/Graphics.hpp>

class MapPackLoader
{
public:
	struct MapFile
	{
		std::string name;
		std::string path;
		sf::Vector2i size;

		MapFile()
		{ }

		MapFile(std::string & name, std::string & path, sf::Vector2i & size) 
			: name(name), path(path), size(size)
		{ }
	};

	typedef std::vector<MapFile> FileList;

	MapPackLoader();
	~MapPackLoader();

	FileList getFiles(int player_number);

private:
	MapFile checkFile(WIN32_FIND_DATA file, int players, bool & result);
};

