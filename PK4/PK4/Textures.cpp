#include "Textures.h"

const TilesetLoadData Textures::FIELDS = TilesetLoadData("gfx\\fields.png", sf::Vector2i(40, 40), 2);
const TilesetLoadData Textures::UNITS = TilesetLoadData("gfx\\units.png", sf::Vector2i(20, 20), 1);
const TilesetLoadData Textures::MISC = TilesetLoadData("gfx\\misc.png", sf::Vector2i(40, 40), 1);

Tileset * Textures::fields = NULL;
Tileset * Textures::units = NULL;
Tileset * Textures::misc = NULL;


void Textures::init()
{	
	fields = new Tileset(FIELDS);
	units = new Tileset(UNITS);
	misc = new Tileset(MISC);
}

void Textures::end()
{
	//TO::FIX
	//delete fields;
	//delete units;
	//delete misc;
}

Textures::Textures()
{

}
Textures::~Textures()
{
}

//https://leanpub.com/tdd-ebook