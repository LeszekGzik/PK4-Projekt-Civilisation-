#include "ContextInfo.h"

const float ContextInfo::TEXT_INTERVAL = 4;
const int ContextInfo::FONT_SIZE = 12;
const sf::Color ContextInfo::RECT_COLOR = sf::Color(200, 200, 200, 200);

ContextInfo::ContextInfo()
{
}

ContextInfo::~ContextInfo()
{
	delete[this->count] this->lines;
}

void ContextInfo::set(PixelCoords coords, ContextInfoContent content)
{
	delete[this->count] this->lines;
	this->count = content.size();
	
	if (this->count == 0)
		return;

	this->lines = new sf::Text[this->count];

	this->lines[0].setColor(content[0].color);
	this->lines[0].setString(content[0].string);
	this->lines[0].setCharacterSize(FONT_SIZE);
	float line_height = this->lines[0].getLocalBounds().height + TEXT_INTERVAL;
	float max_width = this->lines[0].getLocalBounds().width;
	this->lines[0].setPosition(coords.x, coords.y + line_height);

	for (int i = 0; i < this->count; i++)
	{
		this->lines[i].setColor(content[i].color);
		this->lines[i].setString(content[i].string);
		this->lines[i].setCharacterSize(FONT_SIZE);
		this->lines[i].setPosition(coords.x, coords.y + line_height);
		if (this->lines[i].getLocalBounds().width > max_width)
			max_width = this->lines[i].getLocalBounds().width;
	}

	initRect(coords, line_height, max_width);
}

void ContextInfo::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (active)
	{
		target.draw(shape, states);
		for (int i = 0; i < this->count; i++)
			target.draw(this->lines[i], states);
	}
}

void ContextInfo::initRect(PixelCoords coords, float height, float width)
{
	this->shape.setPosition(coords);
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(RECT_COLOR);
}
