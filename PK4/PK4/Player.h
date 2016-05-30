#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "GameDefinitions.h"

class Player
{
private:
	int id;
	Color color;
	std::string name;

public:
	Color getColor() { return color; }
	int getId() { return id; }
	std::string& getName() { return name; }

	inline bool operator== (Player& operand) { return this->id == operand.getId(); }
	inline bool operator!= (Player& operand) { return !(*this == operand); }

	Player();
	~Player();
};

