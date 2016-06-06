#include "Button.h"
#include <iostream>

const sf::Color BACK_COLOR(255, 255, 255, 127);
const sf::Color BORDER_COLOR(255, 255, 255, 255);
const sf::Color HL_BACK_COLOR(255, 255, 127, 188);
const sf::Color HL_TEXT_COLOR(0, 0, 0, 255);
const sf::Color TEXT_COLOR(0, 0, 0, 255);
const sf::Vector2u TEXT_POS(8, 8);
const int32_t FONT_SIZE = 32;
const float BORDER_THICKNESS = 0;

Button::Button()
{
}

Button::Button(std::string caption, sf::IntRect position)
	: Component(caption, BACK_COLOR, BORDER_COLOR, TEXT_COLOR, BORDER_THICKNESS, Fonts::fontText(), TEXT_POS, position, FONT_SIZE),
	  highlights(true), highlighted(false)
{
	setHighlightBackColor(HL_BACK_COLOR);
	setHighlightTextColor(HL_TEXT_COLOR);
	setBackColor(BACK_COLOR);
	setTextColor(TEXT_COLOR);
}

Button::~Button()
{
}


void Button::mouseEnter(sf::Event::MouseMoveEvent & args)
{
	eventMouseEnter().invoke(*this, args);
	if (highlights)
		highlightOn();
}

void Button::mouseLeave(sf::Event::MouseMoveEvent & args)
{
	eventMouseLeave().invoke(*this, args);
	if (highlights)
		highlightOff();
}

void Button::refresh()
{
	highlightOff();
}

void Button::setBackColor(sf::Color color)
{
	this->back_color = color;
	if (!highlighted)
		getRect().setFillColor(color);
}

void Button::setTextColor(sf::Color color)
{
	this->text_color = color;
	if (!highlighted)
		getText().setColor(color);
}

void Button::highlightOn()
{
	this->highlighted = true;
	getRect().setFillColor(this->highlight_back_color);
	getText().setColor(this->highlight_text_color);
}

void Button::highlightOff()
{
	this->highlighted = false;
	getRect().setFillColor(this->back_color);
	getText().setColor(this->text_color);
}
