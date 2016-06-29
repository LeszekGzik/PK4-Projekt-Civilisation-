#pragma once
#include <SFML/Graphics.hpp>
#define HEX_NEIGHBOURS 6

enum LoopExitCode { Exit, Menu, Play };

const static struct ENGINE
{
	static const char* file_name[3];
	static const float basic_unit;
	static const float flag_size_factor;
	static const float scroll_speed;
	static const float scroll_distance;
	static const int dijsktra_max_steps = 500;
	static const int min_players = 2;
	static const int max_players = 4;
};

typedef sf::Vector2f PixelCoords;
typedef sf::VertexArray DrawableObject;
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

class Neighbours
{
public:
	static const sf::Vector2i neighbours[2][6];

	static OffsetCoords get(OffsetCoords field, int32_t n);
};