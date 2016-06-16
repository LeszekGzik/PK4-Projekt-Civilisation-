#include "Settlement.h"

const int Settlement::TEX_ID = 2;
const int Settlement::TEXT_TOP = 5;
const int Settlement::CHAR_SIZE = 20;
TexturedHex * Settlement::style = nullptr;

void Settlement::setTextPosition()
{
	sf::FloatRect bounds = text.getLocalBounds();
	sf::Vector2i sett_pos = getPosition();
	sf::Vector2f text_pos;
	text_pos.x = sett_pos.x + (style->horizontalSize() - bounds.width) / 2;
	text_pos.y = sett_pos.y + style->verticalSize() + TEXT_TOP;
	text.setPosition(text_pos);
}

void Settlement::setStyle(Hex * hex)
{
	style = new TexturedHex(*hex);
}

void Settlement::clear()
{
	if (style != nullptr)
		delete style;
}

Settlement::Settlement(AxialCoords position, Player& owner) : InGameObject(position, owner)
{
}


Settlement::~Settlement()
{
}

void Settlement::init()
{
	this->tileset = &Textures::tilesetMisc();

	this->text.setFont(Fonts::fontText());
	this->text.setColor(ColorUtils::sfColor(getOwner().getColor()));
	this->text.setCharacterSize(CHAR_SIZE);
	this->text.setString(getOwner().getName());
	setTextPosition();

	this->tile = style->create(getPosition(), Textures::tilesetMisc(), TEX_ID);
}

CombatResult Settlement::attacked(float strength, int & counter_damage)
{
	return CombatResult();
}

void Settlement::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(tile, &tileset->getTileset());
	target.draw(text, states);
}

void Settlement::move(AxialCoords coords)
{
}

void Settlement::move(PixelCoords coords)
{
}

void Settlement::newTurn()
{
}

void Settlement::select(bool selected)
{
}

ContextInfoContent * Settlement::getContextInfoContent()
{
	return nullptr;
}
