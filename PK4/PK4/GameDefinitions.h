#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum Color {Red, Blue, Green, Yellow};

class ColorUtils
{
private:
	static const sf::Color COLOR_RED;
	static const sf::Color COLOR_BLUE;
	static const sf::Color COLOR_GREEN;
	static const sf::Color COLOR_TRANSPARENT;
	static const int ALPHA = 127;

public:
	static sf::Color sfColor(Color color);
	static sf::Color sfMask(Color color);

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
	MapSettings map_settings;
	PlayerSettings player_settings;
	
	InitSettings(MapSettings _map_settings, PlayerSettings _player_settings)
	{
		map_settings = _map_settings;
		player_settings = _player_settings;
	}
};

