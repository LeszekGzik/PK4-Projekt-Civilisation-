#pragma once
#include "Field.h"
#include "PearlsDeposit.h"

class Water :
	public Field
{
private:

public:
	Water(OffsetCoords position);
	~Water();
};

