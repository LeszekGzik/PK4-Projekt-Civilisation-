#include "Desert.h"

const FieldType TYPE = Impassable;
const int ID = 2;
const int MOVEMENT_COST = 2;

Desert::Desert(OffsetCoords position) : Field(ID, position, MOVEMENT_COST, TYPE)
{
}


Desert::~Desert()
{
}
