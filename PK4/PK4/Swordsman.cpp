#include "Swordsman.h"
#include "Pillage.h"

namespace
{
	const std::string NAME = "SWORDSMAN";
	const int ID = 2;
	const int SPEED = 2;
	const int STRENGTH = 9;
	const UnitType TYPE = UnitType::Land;
}

int Swordsman::checkMovement(Field * field)
{
	if (field->getType() != FieldType::Land)
		return _unreachable;
	else if (checkIfOccupied(field) == Occupied::Full)
		return _unreachable;
	else
		return field->getMovementCost();
}

Swordsman::Swordsman(Field* field, Player & owner) : Unit(ID, field, owner, NAME, SPEED, STRENGTH, TYPE)
{
	grantAbility<Pillage>();
}


Swordsman::~Swordsman()
{
}
