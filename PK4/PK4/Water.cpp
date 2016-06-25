#include "Water.h"

namespace
{
	const FieldType TYPE = FieldType::Sea;
	int ID = 3;
	const int MOVEMENT_COST = 1;
}

Water::Water(OffsetCoords position) : Field(ID, position, MOVEMENT_COST, TYPE)
{
}

Water::~Water()
{
}
