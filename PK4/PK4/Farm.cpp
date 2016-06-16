#include "Farm.h"

const int Farm::ID = 1;

Farm::Farm(OffsetCoords position, Player& owner) : Improvement(position, owner, ID)
{
}


Farm::~Farm()
{
}
