#include "Worker.h"
#include "Abilities.h"

namespace
{
	const std::string NAME = "WORKER";
	const int ID = 3;
	const int SPEED = 2;
	const int STRENGTH = 0;
	const UnitType TYPE = UnitType::Worker;
}

Worker::Worker(Field * field, Player & owner) : Unit(ID, field, owner, NAME, SPEED, STRENGTH, TYPE)
{
	grantAbility<Pillage>();
	grantAbility<ConstructFarm>();
	grantAbility<ConstructBarracks>();
	grantAbility<ConstructLumberjacksHut>();
	grantAbility<ConstructIronMine>();
}

Worker::~Worker()
{
}

int Worker::checkMovement(Field * field)
{
	if (field->getType() != FieldType::Land)
		return -1;
	else if (checkIfOccupied(field) == Occupied::Full)
		return -1;
	else
		return field->getMovementCost();
}
