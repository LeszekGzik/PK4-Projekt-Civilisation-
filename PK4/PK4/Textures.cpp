#include "Textures.h"

const TilesetLoadData Textures::FIELDS = TilesetLoadData("gfx\\fields.png", sf::Vector2i(40, 40), 40);

void Textures::init()
{	
	//Tileset * t = new Tileset(FIELDS);
	fields = new Tileset(FIELDS);
}

void Textures::end()
{
	//delete Textures::fields;
}

Textures::Textures()
{

}
Textures::~Textures()
{
}

//https://leanpub.com/tdd-ebook