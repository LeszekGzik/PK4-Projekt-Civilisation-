#pragma once
#include <SFML/Graphics.hpp>
#include "InGameObject.h"
#include "GameDefinitions.h"
#include "EngineDefinitions.h"
#include "Textures.h"
#include "TexturedHex.h"
#include "ObjectStyle.h"
#include "Player.h"
#include "Field.h"
#include <algorithm>
#include <list>
#include <string>
#include <queue>
#include <vector>

class Field;

class Unit : public InGameObject
{
private:
	int id;
	int misc_id;
	bool selected;
	sf::Sprite banner;
	sf::Sprite token;
	std::string name;

	int health = 100;
	int strength;
	int speed;
	int movement_points;

public:
	static Tileset& unitTileset() { return Textures::tilesetUnits(); }
	static Tileset& miscTileset() { return Textures::tilesetMisc(); }

	void init();

	virtual void setHealth(int health) { this->health = health; }
	virtual void setMovementPoints(int points) { this->movement_points = points; }
	virtual void setName(std::string& name) { this->name = name; }
	virtual void setSpeed(int speed) { this->speed = speed; }
	virtual void setStrength(int strength) { this->strength = strength; }

	virtual int getHealth() { return this->health; }
	virtual int getMovementPoints() { return this->movement_points; }
	virtual std::string & getName() { return name; }
	virtual int getSpeed() { return this->speed; }
	virtual int getStrength() { return this->strength; }

	Unit(int id, AxialCoords position, Player& owner);
	Unit(int id, AxialCoords position, Player& owner, std::string const& name, int speed, int strength);
	~Unit();

	virtual CombatResult attack(InGameObject * target);
	virtual CombatResult attacked(float strength, int & counter_damage);
	virtual Occupied checkIfOccupied(Field * field);
	virtual int checkMovement(Field * field) abstract;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void move(AxialCoords coords);
	virtual void move(PixelCoords coords);
	virtual void newTurn();
	virtual void select(bool selected);
	virtual ContextInfoContent * getContextInfoContent();
};

