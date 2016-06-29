#include "Hills.h"

namespace
{
	const FieldType TYPE = FieldType::Land;
	int ID = 5;
	const int MOVEMENT_COST = 2;
}


Hills::Hills(OffsetCoords position) : Field(ID, position, MOVEMENT_COST, TYPE)
{
}

Hills::~Hills()
{
}
