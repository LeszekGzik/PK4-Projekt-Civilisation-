#include "CheckBox.h"

namespace
{
	const sf::Color BACK_COLOR(255, 255, 255, 0);
	const sf::Color BORDER_COLOR(255, 255, 255, 255);
	const sf::Color TEXT_COLOR(0, 0, 0, 255);
	const sf::Vector2u TEXT_POS(4, 4);
	const int32_t FONT_SIZE = 32;
	const float BORDER_THICKNESS = 0;
}

CheckBox::CheckBox() 
{
	init();
}

CheckBox::CheckBox(std::string & caption, sf::IntRect & bounds)
 : Component(caption, BACK_COLOR, BORDER_COLOR, TEXT_COLOR, BORDER_THICKNESS, Fonts::fontText(), TEXT_POS, bounds, FONT_SIZE)
{
	init();
}


CheckBox::~CheckBox()
{
}

void CheckBox::clicked(sf::Event::MouseButtonEvent & args)
{
	this->checked = !this->checked;
	this->box.setTextureRect(this->tileset.getTile(this->checked ? CHECKED : UNCHECKED));
	eventClicked().invoke(*this, args);
}

void CheckBox::init()
{
	sf::IntRect const& pos = getPosition();
	sf::Vector2i tile_size = this->tileset.getTileSize();
	float scale = (float)pos.height / tile_size.y;

	box.setScale(scale, scale);
	box.setPosition(pos.left + pos.width - tile_size.x * scale, pos.top);
	box.setTexture(this->tileset.getTileset());
	box.setTextureRect(this->tileset.getTile(UNCHECKED));

	this->checked = false;
}

void CheckBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (getVisible())
	{
		target.draw(getRect());
		target.draw(getText());
		target.draw(box);
	}
}
