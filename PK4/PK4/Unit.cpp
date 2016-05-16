#include "Unit.h"

const sf::Vector2f Unit::DEfAULT_FLAG_SIZE = sf::Vector2f(20, 20);

TexturedHex Unit::hex_style;
Flag Unit::flag_style;

void Unit::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(vertex, &miscTileset().getTileset());
	target.draw(flag);
}

void Unit::initFlag(OffsetCoords position)
{
	PixelCoords position_px = flag_style.getPosition(hex_style, position);
	Tileset& tileset = unitTileset();
	flag.move(position_px);
	flag.setTexture(tileset.getTileset());
	flag.setTextureRect(tileset.getTile(id));
	flag.setScale(flag_style.getScale());
}

Unit::Unit(int id, OffsetCoords position, Player& _owner) : owner(_owner), misc_id(DEFAULT_MISC_ID), id(id), InGameObject()
{
	vertex = hex_style.create(position, miscTileset(), misc_id);
	initFlag(position);
}

Unit::~Unit()
{
}
