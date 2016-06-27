#include "Dragon.h"

namespace
{
	const std::string NAME = "DRAGON";
	const int ID = 1;
	const int SPEED = 5;
	const int STRENGTH = 30;
	const UnitType TYPE = UnitType::Air;
}


Dragon::Dragon(Field * field, Player & owner) : Unit(ID, field, owner, NAME, SPEED, STRENGTH, TYPE)
{
	grantAbility<Pillage>();
}

Dragon::~Dragon()
{
}

int Dragon::checkMovement(Field * field)
{
	if (checkIfOccupied(field) == Occupied::Full)
		return -1;
	else
		return 1;
}
