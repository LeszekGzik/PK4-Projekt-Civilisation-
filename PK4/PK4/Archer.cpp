#include "Archer.h"

const std::string NAME = "ARCHER";
const int SPEED = 2;
const int STRENGTH = 6;

int Archer::checkMovement(Field * field)
{
	if (field->getType() != FieldType::Land)
		return -1;
	else if (checkIfOccupied(field) == Occupied::Full)
		return -1;
	else
		return field->getMovementCost();
}

Archer::Archer(AxialCoords position, Player& owner) : Unit(Archer::ID, position, owner, NAME, 2, STRENGTH)
{
}

Archer::~Archer()
{
}
