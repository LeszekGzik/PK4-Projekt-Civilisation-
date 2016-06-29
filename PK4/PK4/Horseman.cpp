#include "Horseman.h"


namespace
{
	const std::string NAME = "HORSEMAN";
	const int ID = 5;
	const int SPEED = 4;
	const int STRENGTH = 6;
	const UnitType TYPE = UnitType::Land;
}


Horseman::Horseman(Field * field, Player & owner) : Unit(ID, field, owner, NAME, SPEED, STRENGTH, TYPE)
{
	grantAbility<Pillage>();
}

Horseman::~Horseman()
{
}

int Horseman::checkMovement(Field * field)
{
	if (field->getType() != FieldType::Land)
		return -1;
	else if (checkIfOccupied(field) == Occupied::Full)
		return -1;
	else
		return field->getMovementCost();
}
