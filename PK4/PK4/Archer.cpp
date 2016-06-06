#include "Archer.h"

const std::string NAME = "ARCHER";
const int SPEED = 2;

Archer::Archer(AxialCoords position, Player& owner) : Unit(Archer::ID, position, owner, NAME, 2)
{
}

Archer::~Archer()
{
}
