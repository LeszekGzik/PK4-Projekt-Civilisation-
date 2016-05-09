#include "Textures.h"

const TilesetLoadData Textures::FIELDS = TilesetLoadData("gfx\\fields.png", sf::Vector2i(40, 40), 40);

void Textures::init()
{	

	fields->setTexture(FIELDS);
}

void Textures::end()
{
	delete fields;
}

Textures::Textures()
{

}
Textures::~Textures()
{
}

//https://leanpub.com/tdd-ebook