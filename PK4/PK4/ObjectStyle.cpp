#include "ObjectStyle.h"


PixelCoords ObjectStyle::flagPosition(OffsetCoords position)
{
	PixelCoords position_px = hex_style.toPixel(position);
	position_px.x += (hex_style.horizontalSize() - flag_size.x) / 2;
	position_px.y += (hex_style.verticalSize() - flag_size.y) / 2;

	return position_px;
}

void ObjectStyle::scaleFlag(sf::Sprite & sprite)
{
	sf::Vector2i tile = Textures::tilesetUnits().getTileSize();
	sprite.scale(flag_size.x / tile.x, flag_size.y / tile.y);
}

void ObjectStyle::scaleToken(sf::Sprite & sprite)
{
	sf::Vector2i tile = Textures::tilesetMisc().getTileSize();
	sprite.setScale(size.x / tile.x, size.y / tile.y);
}

sf::Sprite ObjectStyle::createFlag(OffsetCoords position, int texture_id)
{
	PixelCoords position_px = flagPosition(position);
	sf::Sprite flag(unitTileset.getTileset(), unitTileset.getTile(texture_id));
	flag.move(position_px);
	scaleFlag(flag);
	return flag;
}

sf::Sprite ObjectStyle::createToken(OffsetCoords position, int texture_id, Player player)
{
	PixelCoords position_px = hex_style.toPixel(position);
	sf::Sprite token(miscTileset.getTileset(), miscTileset.getTile(texture_id));
	token.setColor(ColorUtils::sfColor(player.getColor()));
	scaleToken(token);
	float temp = (hex_style.horizontalSize() - miscTileset.getTileSize().x * token.getScale().x) * 0.5;
	token.setPosition(sf::Vector2f((float)position_px.x + temp, (float)position_px.y));
	return token;
}

void ObjectStyle::move(OffsetCoords position, sf::Sprite& sprite)
{
	PixelCoords pos = sprite.getPosition();
	sprite.move(hex_style.toPixel(position) - pos);
}

void ObjectStyle::move(PixelCoords position, sf::Sprite& sprite)
{
	PixelCoords pos = sprite.getPosition();
	sprite.move(hex_style.toPixel(hex_style.toAxial(position)) - pos);
}

ObjectStyle::ObjectStyle(Hex& hex_style) 
	: hex_style(hex_style), unitTileset(Textures::tilesetUnits()), miscTileset(Textures::tilesetMisc())
{
	float _size_u = hex_style.verticalSize();
	float _factor = ENGINE::flag_size_factor;
	size = sf::Vector2f(_size_u, _size_u);
	flag_size = sf::Vector2f(_size_u * _factor, _size_u * _factor);
}


ObjectStyle::~ObjectStyle()
{
}
