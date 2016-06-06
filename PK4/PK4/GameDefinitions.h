#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum Color { Red, Blue, Green, Yellow };

class ColorUtils
{
public:
	static sf::Color sfColor(Color color, int alpha = 255);
	static sf::Color sfMask(Color color);
	static Color next(Color color);
	static Color prev(Color color);

private:
	static const int ALPHA = 255;

};

struct MapSettings
{
	sf::Vector2i size;

	MapSettings(sf::Vector2i _size) : size(_size)
	{

	}
	MapSettings()
	{

	}
};

struct PlayerSettings
{
	int count;
	std::string * names;
	Color * colors;

	PlayerSettings(int _count, std::string _names[], Color _colors[])
	{
		count = _count;
		colors = _colors;
		names = _names;
	}

	PlayerSettings()
	{

	}
};

struct WorldSettings
{

};

struct InitSettings
{
	MapSettings map;
	PlayerSettings player;
	
	InitSettings(MapSettings _map_settings, PlayerSettings _player_settings) : map(_map_settings), player(_player_settings)
	{
	}
};

