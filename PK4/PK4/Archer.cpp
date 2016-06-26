#include "Archer.h"
#include "Pillage.h"

namespace
{
	const std::string NAME = "ARCHER";
	const int ID = 1;
	const int SPEED = 2;
	const int STRENGTH = 6;
	const UnitType TYPE = UnitType::Land;
}

int Archer::checkMovement(Field * field)
{
	if (field->getType() != FieldType::Land)
		return -1;
	else if (checkIfOccupied(field) == Occupied::Full)
		return -1;
	else
		return field->getMovementCost();
}

Archer::Archer(Field* field, Player& owner) : Unit(ID, field, owner, NAME, SPEED, STRENGTH, TYPE)
{
	grantAbility<Pillage>();
}

Archer::~Archer()
{
}
