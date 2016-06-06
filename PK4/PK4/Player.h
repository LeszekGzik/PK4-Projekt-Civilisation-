#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "GameDefinitions.h"

class Player
{
private:
	int id;
	Color color = Red;
	std::string name;

public:
	void setColor(Color color) { this->color = color; }
	void setId(int id) { this->id = id; }
	void setName(std::string & name) { this->name = name; }

	Color getColor() { return color; }
	int getId() { return id; }
	std::string& getName() { return name; }

	inline bool operator== (Player& operand) { return this->id == operand.getId(); }
	inline bool operator!= (Player& operand) { return !(*this == operand); }

	Player();
	Player(std::string & name, Color color);
	~Player();
};

