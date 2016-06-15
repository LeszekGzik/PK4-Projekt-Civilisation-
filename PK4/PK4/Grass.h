#pragma once
#include "Field.h"

class Grass : public Field
{
private:
	static const FieldType TYPE = Land;
	static const int ID = 1;
	static const int MOVEMENT_COST = 1;

public:
	Grass(OffsetCoords offset_position);
	~Grass();
};

