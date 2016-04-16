#include "BorderMenu.h"



BorderMenu::BorderMenu(sf::IntRect rectangle, std::string corner_path, std::string edge_path)
{
	texture_corner.loadFromFile(corner_path);
	texture_edge.loadFromFile(edge_path);
	texture_edge.setRepeated(true);

	sprite_corner_leftTop.setTexture(texture_corner);
	sprite_corner_rightTop.setTexture(texture_corner);
	sprite_corner_leftBottom.setTexture(texture_corner);
	sprite_corner_rightBottom.setTexture(texture_corner);
	sprite_edge_top.setTexture(texture_edge);
	sprite_edge_left.setTexture(texture_edge);
	sprite_edge_bottom.setTexture(texture_edge);
	sprite_edge_right.setTexture(texture_edge);

	sprite_corner_rightTop.rotate(90);
	sprite_corner_rightBottom.rotate(180);
	sprite_corner_leftBottom.rotate(270);
	sprite_edge_left.rotate(270);
	sprite_edge_bottom.rotate(180);
	sprite_edge_right.rotate(90);

	sprite_corner_leftTop.setPosition(sf::Vector2f(rectangle.left, rectangle.top));
	sprite_corner_rightTop.setPosition(sf::Vector2f(rectangle.width + rectangle.left - TEXTURE_SIZE, rectangle.top));
	sprite_corner_leftBottom.setPosition(sf::Vector2f(rectangle.left, rectangle.height + rectangle.top - TEXTURE_SIZE));
	sprite_corner_rightBottom.setPosition(sf::Vector2f(rectangle.width + rectangle.left - TEXTURE_SIZE, rectangle.height + rectangle.top - TEXTURE_SIZE));

	sprite_edge_top.setTextureRect(sf::IntRect(0, 0, rectangle.width - TEXTURE_SIZE * 3, TEXTURE_SIZE));
	sprite_edge_right.setTextureRect(sf::IntRect(0, 0, rectangle.width - TEXTURE_SIZE * 3, TEXTURE_SIZE));
	sprite_edge_bottom.setTextureRect(sf::IntRect(0, 0, rectangle.width - TEXTURE_SIZE * 3, TEXTURE_SIZE));
	sprite_edge_left.setTextureRect(sf::IntRect(0, 0, rectangle.width - TEXTURE_SIZE * 3, TEXTURE_SIZE));

	sprite_edge_top.setPosition(sf::Vector2f(rectangle.left + TEXTURE_SIZE, rectangle.top));
	sprite_edge_right.setPosition(sf::Vector2f(rectangle.left + rectangle.height - TEXTURE_SIZE, rectangle.top + TEXTURE_SIZE));
	sprite_edge_bottom.setPosition(sf::Vector2f(rectangle.left + rectangle.height - TEXTURE_SIZE * 2, rectangle.top + rectangle.width - TEXTURE_SIZE));
	sprite_edge_left.setPosition(sf::Vector2f(rectangle.left, rectangle.top + rectangle.width - TEXTURE_SIZE * 2));

	shape_body.setSize(sf::Vector2f(rectangle.height - TEXTURE_SIZE * 3, rectangle.width - TEXTURE_SIZE * 3));
	shape_body.setPosition(sf::Vector2f(rectangle.left + TEXTURE_SIZE, rectangle.top + TEXTURE_SIZE));
	shape_body.setFillColor(sf::Color(70, 42, 177));
	
}

BorderMenu::~BorderMenu()
{
}

void BorderMenu::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(sprite_corner_leftTop);
	window.draw(sprite_corner_rightTop);
	window.draw(sprite_corner_leftBottom);
	window.draw(sprite_corner_rightBottom);
	window.draw(sprite_edge_top);
	window.draw(sprite_edge_right);
	window.draw(sprite_edge_left);
	window.draw(sprite_edge_bottom);
	window.draw(shape_body);
}

void BorderMenu::setColor(sf::Color color)
{
	sprite_corner_leftBottom.setColor(color);

}
