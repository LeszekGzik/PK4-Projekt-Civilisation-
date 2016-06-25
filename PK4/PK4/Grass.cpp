#include "Grass.h"


namespace
{
	const FieldType TYPE = Land;
	const int ID = 1;
	const int MOVEMENT_COST = 1;
}

Grass::Grass(OffsetCoords offset_position) : Field(ID, offset_position, MOVEMENT_COST, TYPE)
{

}


Grass::~Grass()
{
}
