#include "Deposit.h"

Hex * Deposit::style = nullptr;

void Deposit::init()
{
	Tileset & tileset = Textures::tilesetMisc();
	sf::Vector2f position = style->toPixel(field->getPosition());
	float scale = ENGINE::basic_unit / tileset.getTileSize().x;
	
	position.x -= ((float)tileset.getTileSize().x * scale - style->horizontalSize()) / 2;

	sprite.setScale(scale, scale);
	sprite.setTexture(tileset.getTileset());
	sprite.setPosition(position);
	sprite.setTextureRect(tileset.getTile(this->id));
}


Deposit::Deposit(Field * field, uint32_t id) : field(field), id(id)
{
	init();
}

Deposit::~Deposit()
{
}

void Deposit::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->sprite, states);
}
