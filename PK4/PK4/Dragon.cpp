#include "Dragon.h"

namespace
{
	const std::string NAME = "DRAGON";
	const int ID = 6;
	const int SPEED = 5;
	const int STRENGTH = 24;
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
		return _unreachable;
	else
		return 1;
}
