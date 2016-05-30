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
}

Label::Label()
{
}


Label::~Label()
{
}
