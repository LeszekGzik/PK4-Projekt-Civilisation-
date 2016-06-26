#pragma once
#include "Unit.h"
class Swordsman :
	public Unit
{
public:
	int checkMovement(Field * field);

	Swordsman(Field* field, Player & owner);
	~Swordsman();
};

