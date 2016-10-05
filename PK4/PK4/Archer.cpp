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

const float Archer::HILL_STR_FACTOR = 2;

int Archer::checkMovement(Field * field)
{
	if (field->getType() != FieldType::Land)
		return _unreachable;
	else if (checkIfOccupied(field) == Occupied::Full)
		return _unreachable;
	else
		return field->getMovementCost();
}

float Archer::getTotalStrength()
{
	float base = (float)getHealth() * (float)getStrength() / 100;
	return (dynamic_cast<Hills*>(getField()) != nullptr) ? base * HILL_STR_FACTOR : base;
}

Archer::Archer(Field* field, Player& owner) : Unit(ID, field, owner, NAME, SPEED, STRENGTH, TYPE)
{
	grantAbility<Pillage>();
}

Archer::~Archer()
{
}
