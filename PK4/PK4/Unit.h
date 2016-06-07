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
	int strength;
	int speed;

	static ObjectStyle * object_style;
public:
	static Tileset& unitTileset() { return Textures::tilesetUnits(); }
	static Tileset& miscTileset() { return Textures::tilesetMisc(); }
	static void setStyle(TexturedHex * style);

	void init();

	virtual void setHealth(int health) { this->health = health; }
	virtual void setName(std::string& name) { this->name = name; }
	virtual void setOwner(Player & owner) { this->owner = owner; }
	virtual void setSpeed(int speed) { this->speed = speed; }
	virtual void setStrength(int strength) { this->strength = strength; }

	virtual int getHealth() { return this->health; }
	virtual std::string & getName() { return name; }
	virtual Player & getOwner() { return owner; }
	virtual int getSpeed() { return this->speed; }
	virtual int getStrength() { return this->strength; }

	Unit(int id, AxialCoords position, Player& owner);
	Unit(int id, AxialCoords position, Player& owner, std::string const& name, int speed, int strength);
	~Unit();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void move(AxialCoords coords);
	virtual void move(PixelCoords coords);
	virtual void select(bool selected);
	virtual ContextInfoContent * getContextInfoContent();
};

