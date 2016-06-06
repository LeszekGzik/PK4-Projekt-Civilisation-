#pragma once
#include <SFML/Graphics.hpp>
#include "InGameObject.h"
#include "GameDefinitions.h"
#include "EngineDefinitions.h"
#include "Textures.h"
#include "TexturedHex.h"
#include "ObjectStyle.h"
#include "Player.h"
#include <algorithm>
#include <list>
#include <string>

class Unit : public InGameObject
{
private:
	int id;
	int misc_id;
	bool selected;
	Player& owner;
	sf::Sprite flag;
	sf::Sprite token;
	std::string name;

	int health = 100;
	int speed;

	static ObjectStyle * object_style;
public:
	static Tileset& unitTileset() { return Textures::tilesetUnits(); }
	static Tileset& miscTileset() { return Textures::tilesetMisc(); }
	static void setStyle(TexturedHex * style);

	void init();

	void setName(std::string& name) { this->name = name; }
	std::string & getName() { return name; }
	void setHealth(int health) { this->health = health; }
	int getHealth() { return this->health; }
	void setOwner(Player & owner) { this->owner = owner; }
	Player & getOwner() { return owner; }
	void setSpeed(int speed) { this->speed = speed; }
	int getSpeed() { return this->speed; }

	Unit(int id, AxialCoords position, Player& owner);
	Unit(int id, AxialCoords position, Player& owner, std::string const& name, int speed);
	~Unit();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void move(AxialCoords coords);
	virtual void move(PixelCoords coords);
	virtual void select(bool selected);
	virtual ContextInfoContent * getContextInfoContent();
};

