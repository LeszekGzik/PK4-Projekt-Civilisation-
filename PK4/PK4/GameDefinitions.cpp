#include "GameDefinitions.h"

sf::Color ColorUtils::sfColor(Color color, int alpha)
{
	sf::Color ret_color;
	switch (color)
	{
	case Red:
		ret_color = sf::Color::Red;
		break;
	case Blue:
		ret_color = sf::Color::Blue;
		break;
	case Green:
		ret_color = sf::Color::Green;
		break;
	case Yellow:
		ret_color = sf::Color::Yellow;
		break;
	default:
		return sf::Color::Transparent;
	}
	ret_color.a = alpha;
	return ret_color;
}

sf::Color ColorUtils::sfMask(Color color)
{
	sf::Color _color = sfColor(color);
	_color.a = ALPHA;
	return _color;
}

Color ColorUtils::next(Color color)
{
	if (color == Color::Yellow)
		return Color::Red;
	else
	{
		int ret_color = (int)color;
		return (Color)(++ret_color);
	}
}

Color ColorUtils::prev(Color color)
{
	if (color == Color::Red)
		return Color::Yellow;
	else
	{
		int ret_color = (int)color;
		return (Color)(--ret_color);
	}
}
