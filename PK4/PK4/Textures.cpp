#include "Textures.h"

const TilesetLoadData Textures::FIELDS = TilesetLoadData("gfx\\fields.png", sf::Vector2i(40, 40), 40);
const TilesetLoadData Textures::UNITS = TilesetLoadData("gfx\\units.png", sf::Vector2i(40, 40), 40);
const TilesetLoadData Textures::MISC = TilesetLoadData("gfx\\misc.png", sf::Vector2i(40, 40), 40);

Tileset * Textures::fields = NULL;
Tileset * Textures::units = NULL;
Tileset * Textures::misc = NULL;


void Textures::init()
{	
	fields = new Tileset(FIELDS);
	units = new Tileset(UNITS);
}

void Textures::end()
{
	//TO::FIX
	//delete fields;
	//delete units;
}

Textures::Textures()
{

}
Textures::~Textures()
{
}

//https://leanpub.com/tdd-ebook