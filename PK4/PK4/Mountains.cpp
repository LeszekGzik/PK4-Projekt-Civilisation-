#include "Mountains.h"

namespace
{
	const FieldType TYPE = Impassable;
	const int ID = 4;
	const int MOVEMENT_COST = 1;
}

Mountains::Mountains(OffsetCoords position) : Field(ID, position, MOVEMENT_COST, TYPE)
{
}

Mountains::~Mountains()
{
}
