#include "TextBox.h"

const sf::Color BACK_COLOR(255, 255, 255, 127);
const sf::Color BORDER_COLOR(255, 255, 255, 255);
const sf::Color HL_BACK_COLOR(255, 255, 127, 188);
const sf::Color HL_TEXT_COLOR(0, 0, 0, 255);
const sf::Color TEXT_COLOR(0, 0, 0, 255);
const sf::Vector2u TEXT_POS(8, 8);
const int32_t FONT_SIZE = 32;
const float BORDER_THICKNESS = 0;
const int32_t MAX_LENGTH = 16;
const int32_t BACKSPACE = 8;
const int32_t CARRIAGE_RET = 13;

TextBox::TextBox(std::string caption, sf::IntRect position)
	: Component(caption, BACK_COLOR, BORDER_COLOR, TEXT_COLOR, BORDER_THICKNESS, Fonts::fontText(), TEXT_POS, position, FONT_SIZE),
	highlights(true), highlighted(false)
{
	setHighlightBackColor(HL_BACK_COLOR);
	setHighlightTextColor(HL_TEXT_COLOR);
	setBackColor(BACK_COLOR);
	setTextColor(TEXT_COLOR);
	setMaxLength(MAX_LENGTH);
}

TextBox::TextBox()
{
}


TextBox::~TextBox()
{
}

void TextBox::focusChange()
{
	eventFocusChange().invoke(*this);
	(highlights && highlighted) ? highlightOff() : highlightOn();
}

void TextBox::textEnter(sf::Event::TextEvent& args)
{
	eventKeyDown().invoke(*this, args);
	inputText(args.unicode);
}

void TextBox::refresh()
{
	highlightOff();
}

void TextBox::highlightOn()
{
	Component * base = this;
	this->highlighted = true;
	base->setBackColor(this->highlight_back_color);
	base->setTextColor(this->highlight_text_color);
	update();
}

void TextBox::highlightOff()
{
	Component * base = this;
	this->highlighted = false;
	base->setBackColor(this->back_color);
	base->setTextColor(this->text_color);
	update();
}

void TextBox::inputText(sf::Uint32 character)
{
	std::string& caption = getCaption();
	if (character == BACKSPACE)
	{
		if (caption.length() > 0)
			caption.pop_back();
	}
	else if (character != CARRIAGE_RET)
	{
		if (caption.length() < max_length)
			caption += (char)character;
	}
	update();
}
