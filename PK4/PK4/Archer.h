#pragma once
#include "Unit.h"
#include "EngineDefinitions.h"

class Archer :
	public Unit
{
private:
	static const int ID = 2;

public:
	Archer(OffsetCoords position);
	~Archer();
};

