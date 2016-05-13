#pragma once
#include <SFML/Graphics.hpp>



class Hex
{
public:
	static const float DEFAULT_EDGE;
	static const sf::Color DEFAULT_OUTLINE_COLOR;

	float horizontalSize();
	float verticalSize();
	float edgeSize();
	virtual sf::VertexArray create(sf::Vector2i _position) sealed;

	Hex(float _edge = DEFAULT_EDGE, sf::Color _outline_color = DEFAULT_OUTLINE_COLOR);
	~Hex();

private:

	float edge;
	float horizontal;
	float vertical;
	sf::Color outline_color;
};

