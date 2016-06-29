#pragma once
#include <SFML/Graphics.hpp>
#include <string>

enum Color { Red, Blue, Green, Yellow };
enum FieldType { Impassable, Land, Sea };
enum Occupied { Empty, Full, Enemy };
enum CombatResult { Lose, Tie, Win };
enum ResourceType { Food, Wood, Iron, Gems };
enum class UnitType { Worker, Land, Naval, Air };

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

	~PlayerSettings()
	{
	}
};

struct InitSettings
{
	PlayerSettings player;
	bool fullscreen;
	bool richmode;
	
	InitSettings(PlayerSettings _player_settings, bool fullscreen, bool richmode) 
		: player(_player_settings), fullscreen(fullscreen), richmode(richmode)
	{
	}
};

