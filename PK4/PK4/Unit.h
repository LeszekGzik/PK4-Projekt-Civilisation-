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
#include <queue>
#include <vector>

#define _unreachable -1

class Unit : public InGameObject
{
private:
	int id;
	int misc_id;
	bool selected;
	bool attacked_this_turn = false;
	sf::Sprite banner;
	sf::Sprite token;
	std::string name;

	int health = 100;
	int strength;
	int speed;
	int movement_points;
	UnitType type;

public:
	static Tileset& unitTileset() { return Textures::tilesetUnits(); }
	static Tileset& miscTileset() { return Textures::tilesetMisc(); }

	void init();

	virtual void setHealth(int health) { this->health = health; }
	virtual void setActionPoints(int points) { this->movement_points = points; }
	virtual void setName(std::string& name) { this->name = name; }
	virtual void setSpeed(int speed) { this->speed = speed; }
	virtual void setStrength(int strength) { this->strength = strength; }
	virtual void setType(UnitType type) { this->type = type; }
	virtual void setIfAttackedThisTurn(bool attacked) { this->attacked_this_turn = attacked; }

	virtual int getHealth() { return this->health; }
	virtual int getActionPoints() { return this->movement_points; }
	virtual std::string & getName() { return name; }
	virtual float getTotalStrength();
	virtual int getSpeed() { return this->speed; }
	virtual int getStrength() { return this->strength; }
	virtual UnitType getType() { return this->type; }

	virtual bool canAttack() { return !this->attacked_this_turn; }
	virtual bool hasFullAction() { return this->movement_points == this->speed; }

	Unit(int id, Field* field, Player& owner);
	Unit(int id, Field* field, Player& owner, std::string const& name, int speed, int strength, UnitType type);
	~Unit();

	virtual ManagmentStatus initCombat(Field * field);
	virtual CombatResult attack(InGameObject * target);
	virtual CombatResult attacked(float strength, int & counter_damage);
	virtual void spendActionPoints(uint32_t points);
	virtual Occupied checkIfOccupied(Field * field);
	virtual int checkMovement(Field * field) abstract;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void move(Field * destination);
	virtual void newTurn();
	virtual void select(bool selected);
	virtual ContextInfoContent * getContextInfoContent();
	virtual ContextInfoContent * getContextInfoContent(ContextInfoContent * content);
};

