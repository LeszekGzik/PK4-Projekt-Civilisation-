#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class BorderMenu : public sf::Drawable
{
private:
	sf::Texture texture_corner;
	sf::Texture texture_edge;
	sf::Sprite sprite_corner_leftTop;
	sf::Sprite sprite_corner_rightTop;
	sf::Sprite sprite_corner_rightBottom;
	sf::Sprite sprite_corner_leftBottom;
	sf::Sprite sprite_edge_top;
	sf::Sprite sprite_edge_right;
	sf::Sprite sprite_edge_bottom;
	sf::Sprite sprite_edge_left;
	sf::RectangleShape shape_body;

	const int TEXTURE_SIZE = 32;
public:
	BorderMenu(sf::IntRect, std::string, std::string);
	~BorderMenu();

	void virtual draw(sf::RenderTarget&, sf::RenderStates) const;
	void setColor(sf::Color);
};

