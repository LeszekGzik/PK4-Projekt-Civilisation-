#pragma once
#include "Field.h"

class Grass : public Field
{
private:
	static const int ID = 1;

public:
	Grass(sf::Vector2i offset_position);
	~Grass();
};

