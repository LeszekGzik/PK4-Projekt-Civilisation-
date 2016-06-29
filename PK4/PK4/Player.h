#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include <list>
#include "GameDefinitions.h"
#include "ResourcesHandler.h"

class Player
{
private:
	int id;
	int objects = 0;
	Color color = Red;
	std::string name;
	ResourcesHandler resources;

public:
	void increaseObjects() { this->objects++; }
	void decreaseObjects() { this->objects--; }

	void setColor(Color color) { this->color = color; }
	void setId(int id) { this->id = id; }
	void setName(std::string & name) { this->name = name; }

	Color getColor() { return color; }
	int getId() { return id; }
	std::string& getName() { return name; }
	ResourcesHandler & getResources() { return resources; }
	int getNumberOfObjects() { return this->objects; }

	inline bool operator== (Player& operand) { return this->id == operand.getId(); }
	inline bool operator!= (Player& operand) { return !(*this == operand); }

	Player();
	Player(std::string & name, Color color);
	~Player();
};
