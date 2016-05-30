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

void Button::highlightOn()
{
	Component * base = this;
	this->highlighted = true;
	base->setBackColor(this->highlight_back_color);
	base->setTextColor(this->highlight_text_color);
	update();
}

void Button::highlightOff()
{
	Component * base = this;
	this->highlighted = false;
	base->setBackColor(this->back_color);
	base->setTextColor(this->text_color);
	update();
}
