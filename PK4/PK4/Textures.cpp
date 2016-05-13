#include "Textures.h"

const TilesetLoadData Textures::FIELDS = TilesetLoadData("gfx\\fields.png", sf::Vector2i(40, 40), 40);
const TilesetLoadData Textures::TEST = TilesetLoadData("gfx\\test.png", sf::Vector2i(40, 40), 2);
Tileset * Textures::fields = NULL;
Tileset * Textures::units = NULL;
Tileset * Textures::test = NULL;


void Textures::init()
{	
	//fields = new Tileset(FIELDS);
	test = new Tileset(TEST);
}

void Textures::end()
{
	//delete fields;
	delete[] test;
}

Textures::Textures()
{

}
Textures::~Textures()
{
}

//https://leanpub.com/tdd-ebook