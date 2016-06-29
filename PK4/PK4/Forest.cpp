#include "Forest.h"

namespace
{
	const FieldType TYPE = Land;
	const int ID = 6;
	const int MOVEMENT_COST = 2;
}

Forest::Forest(OffsetCoords position) : Field(ID, position, ID, TYPE)
{

}


Forest::~Forest()
{
}
