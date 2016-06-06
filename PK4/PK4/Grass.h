#pragma once
#include "Field.h"

class Grass : public Field
{
private:
	static const int ID = 1;

public:
	Grass(OffsetCoords offset_position);
	~Grass();
};

