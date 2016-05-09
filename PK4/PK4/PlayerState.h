#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "GameDefinitions.h"

class PlayerState
{
private:
	int id;
	Color color;
	std::string name;

public:
	PlayerState();
	~PlayerState();
};

