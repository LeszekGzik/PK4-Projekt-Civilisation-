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
	highlights(true), highlighted(false), old_caption(caption)
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
	if (!getFocused())
	{
		if (this->caption_changed)
			event_text_change.invoke(*this, this->old_caption);
	}
	else
	{
		this->old_caption = getCaption();
	}
	(highlights && highlighted) ? highlightOff() : highlightOn();
}

void TextBox::textEnter(sf::Event::TextEvent& args)
{
	eventTextEnter().invoke(*this, args);
	inputText(args.unicode);
}

void TextBox::refresh()
{
	highlightOff();
}

void TextBox::setBackColor(sf::Color color)
{
	this->back_color = color;
	if (!highlighted)
		getRect().setFillColor(color);
}

void TextBox::setTextColor(sf::Color color)
{
	this->text_color = color;
	if (!highlighted)
		getText().setColor(color);
}

void TextBox::highlightOn()
{
	this->highlighted = true;
	getRect().setFillColor(this->highlight_back_color);
	getText().setColor(this->highlight_text_color);
}

void TextBox::highlightOff()
{
	this->highlighted = false;
	getRect().setFillColor(this->back_color);
	getText().setColor(this->text_color);
}

void TextBox::inputText(sf::Uint32 character)
{
	std::string caption = getCaption();

	if (character == BACKSPACE)
	{
		if (caption.length() > 0)
		{
			caption.pop_back();
			this->caption_changed = true;
			setCaption(caption);
		}
	}
	else if (character != CARRIAGE_RET)
	{
		if (caption.length() < max_length)
		{
			caption += (char)character;
			this->caption_changed = true;
			setCaption(caption);
		}
	}
}
