#include "GameDefinitions.h"

const sf::Color ColorUtils::COLOR_RED = sf::Color(255, 0, 0);
const sf::Color ColorUtils::COLOR_BLUE = sf::Color(0, 0, 255);
const sf::Color ColorUtils::COLOR_GREEN = sf::Color(0, 255, 0);
const sf::Color ColorUtils::COLOR_TRANSPARENT = sf::Color(255, 255, 255, 255);

sf::Color ColorUtils::sfColor(Color color)
{
	switch (color)
	{
	case Red:
		return COLOR_RED;
	case Blue:
		return COLOR_BLUE;
	case Green:
		return COLOR_GREEN;
	default:
		return COLOR_RED;
	}
}

sf::Color ColorUtils::sfMask(Color color)
{
	sf::Color _color = sfColor(color);
	_color.a = ALPHA;
	return _color;
}
