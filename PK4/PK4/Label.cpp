#include "Label.h"

const sf::Color BACK_COLOR(255, 255, 255, 0);
const sf::Color BORDER_COLOR(255, 255, 255, 255);
const sf::Color TEXT_COLOR(0, 0, 0, 255);
const sf::Vector2u TEXT_POS(8, 8);
const int32_t FONT_SIZE = 32;
const float BORDER_THICKNESS = 0;

Label::Label(std::string caption, sf::IntRect position)
	: Component(caption, BACK_COLOR, BORDER_COLOR, TEXT_COLOR, BORDER_THICKNESS, Fonts::fontText(), TEXT_POS, position, FONT_SIZE)
{
	setDisplayStyle(DisplayStyle::Text);

	sf::IntRect pos = getPosition();
	this->image.setPosition(sf::Vector2f(pos.left, pos.top));
	this->image.setTextureRect(pos);
}

Label::Label()
{
}


Label::~Label()
{
}

void Label::setImage(Tileset & tileset, uint32_t tile)
{
	this->image.setTexture(tileset.getTileset());
	this->image.setTextureRect(tileset.getTile(tile));
	sf::Vector2f scale;
	sf::Vector2i size = tileset.getTileSize();
	sf::IntRect pos = getPosition();
	scale.x = (float)pos.width / size.x;
	scale.y = (float)pos.height / size.y;
	this->image.setScale(scale);
}

void Label::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (getVisible())
	{
		switch (this->display_style)
		{
		default:
		case Text:
			target.draw(getRect(), states);
			target.draw(getText(), states);
		case Image:
			target.draw(getImage(), states);
		}
	}
}
