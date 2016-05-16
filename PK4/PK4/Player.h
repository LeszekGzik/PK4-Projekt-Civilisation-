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
	Player();
	~Player();
};

