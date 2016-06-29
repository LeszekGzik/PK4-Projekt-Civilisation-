#include "Textures.h"

const TilesetLoadData Textures::BUTTONS = TilesetLoadData("gfx\\buttons.png", sf::Vector2i(64, 64));
const TilesetLoadData Textures::IMPROVEMENTS = TilesetLoadData("gfx\\imps.png", sf::Vector2i(40, 40));
const TilesetLoadData Textures::FIELDS = TilesetLoadData("gfx\\fields.png", sf::Vector2i(40, 40));
const TilesetLoadData Textures::UNITS = TilesetLoadData("gfx\\units.png", sf::Vector2i(20, 20));
const TilesetLoadData Textures::MISC = TilesetLoadData("gfx\\misc.png", sf::Vector2i(40, 40));
const TilesetLoadData Textures::CHECKBOX = TilesetLoadData("gfx\\checkbox.png", sf::Vector2i(256, 256));

Tileset * Textures::buttons = nullptr;
Tileset * Textures::improvements = nullptr;
Tileset * Textures::fields = nullptr;
Tileset * Textures::units = nullptr;
Tileset * Textures::misc = nullptr;
Tileset * Textures::checkbox = nullptr;

void Textures::init()
{
	buttons = new Tileset(BUTTONS);
	improvements = new Tileset(IMPROVEMENTS);
	fields = new Tileset(FIELDS);
	units = new Tileset(UNITS);
	misc = new Tileset(MISC);
	checkbox = new Tileset(CHECKBOX);
}

void Textures::end()
{
	//TO::FIX
	//delete buttons;
	//delete improvements;
	//delete fields;
	//delete units;
	//delete misc;
	//delete checkbox;
}

Textures::Textures()
{
}

Textures::~Textures()
{
}

//https://leanpub.com/tdd-ebook