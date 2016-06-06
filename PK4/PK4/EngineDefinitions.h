#pragma once
#include <SFML/Graphics.hpp>

enum LoopExitCode { Exit, Menu, Play };

const static struct ENGINE
{
	static const float basic_unit;
	static const float flag_size_factor;
	static const float scroll_speed;
	static const float scroll_distance;
	static const int min_players = 2;
	static const int max_players = 4;
};


class AxialCoords;

class OffsetCoords : public sf::Vector2i 
{
public:

	OffsetCoords() : sf::Vector2i()
	{
	}

	OffsetCoords(int x, int y) : sf::Vector2i(x, y)
	{
	}

	OffsetCoords(sf::Vector2i const& vec) : sf::Vector2i(vec)
	{
	}

	operator AxialCoords() const;
	bool operator> (OffsetCoords const& arg) const;
	bool operator< (OffsetCoords const& arg) const;

	//PixelCoords toPixel()
};

class AxialCoords : public sf::Vector2i
{
public:

	AxialCoords() : sf::Vector2i()
	{
	}

	AxialCoords(int x, int y) : sf::Vector2i(x, y)
	{
	}

	operator OffsetCoords() const;
};

inline OffsetCoords::operator AxialCoords() const
{
	return AxialCoords(x - y / 2, y);
}

inline bool OffsetCoords::operator> (OffsetCoords const& arg) const
{
	return (this->x > arg.x && this->y > arg.y);
}

inline bool OffsetCoords::operator< (OffsetCoords const& arg) const
{
	return (this->x < arg.x && this->y < arg.y);
}

inline AxialCoords::operator OffsetCoords() const
{
	return OffsetCoords(x + y / 2, y);
}

/*typedef sf::Vector2i OffsetCoords;
typedef sf::Vector2i AxialCoords;*/
typedef sf::Vector2f PixelCoords;
typedef sf::VertexArray DrawableObject;