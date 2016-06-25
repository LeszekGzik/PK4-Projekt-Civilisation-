#include "ContextInfo.h"

const float ContextInfo::CURSOR_OFFSET = 30;
const float ContextInfo::TEXT_INTERVAL = 4;
const float ContextInfo::RECT_OFFSET_VERTICAL = 6;
const float ContextInfo::RECT_OFFSET_HORIZONTAL = 6;
const int ContextInfo::FONT_SIZE = 16;
const sf::Color ContextInfo::RECT_COLOR = sf::Color(200, 200, 200, 200);

ContextInfo::ContextInfo()
{
}

ContextInfo::~ContextInfo()
{
	if (this->count > 0)
		delete[this->count] this->lines;
}

void ContextInfo::set(PixelCoords coords, ContextInfoContent * content)
{	
	if (this->count != 0)
		delete[this->count] this->lines;

	this->count = content->size();
	coords.y += CURSOR_OFFSET * this->aligment;

	if (this->count == 0)
		return;

	if (this->aligment == Aligment::Up)
		std::reverse(content->begin(), content->end());

	this->lines = new sf::Text[this->count];

	this->lines[0].setFont(Fonts::fontText());
	this->lines[0].setColor((*content)[0].color);
	this->lines[0].setString((*content)[0].string);
	this->lines[0].setCharacterSize(FONT_SIZE);
	this->lines[0].setPosition(coords.x, coords.y);

	float line_height = this->lines[0].getLocalBounds().height + TEXT_INTERVAL;
	float max_width = this->lines[0].getLocalBounds().width;
	float total_height = line_height;

	if (this->aligment == Aligment::Up)
		this->lines[0].move(0, -line_height);

	for (int i = 1; i < this->count; i++)
	{
		this->lines[i].setFont(Fonts::fontText());
		this->lines[i].setColor((*content)[i].color);
		this->lines[i].setString((*content)[i].string);
		this->lines[i].setCharacterSize(FONT_SIZE);
		this->lines[i].setPosition(coords.x, coords.y + total_height * this->aligment);
		if (this->aligment == Aligment::Up)
			this->lines[i].move(0, -line_height);
		if (this->lines[i].getLocalBounds().width > max_width)
			max_width = this->lines[i].getLocalBounds().width;
		total_height += line_height;
	}

	this->line_height = line_height;
	initRect(coords, total_height, max_width);
}

void ContextInfo::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (this->active)
	{
		target.draw(shape, states);
		for (int i = 0; i < this->count; i++)
			target.draw(this->lines[i], states);
	}
}

void ContextInfo::initRect(PixelCoords coords, float height, float width)
{
	height += RECT_OFFSET_VERTICAL * 2;
	width += RECT_OFFSET_HORIZONTAL * 2;
	coords.x -= RECT_OFFSET_VERTICAL;
	coords.y -= RECT_OFFSET_HORIZONTAL * this->aligment;
	if (this->aligment == Aligment::Up)
		coords.y -= height;
	this->shape.setPosition(coords);
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(RECT_COLOR);
}

void ContextInfo::update()
{
	for (int i = 0; i < this->count; i++) 
	{
		PixelCoords pos = this->lines[i].getPosition();
		this->lines[i].setPosition(pos.x, pos.y + (2 * RECT_OFFSET_VERTICAL + this->line_height * (2 * i + 1)) * this->aligment);
	}
	PixelCoords pos = this->shape.getPosition();
	this->shape.setPosition(pos.x, pos.y + (2 * RECT_OFFSET_VERTICAL + this->shape.getSize().y) * this->aligment);
}
