#pragma once
#include "Unit.h"
#include "EngineDefinitions.h"

class Archer :
	public Unit
{
private:
	static const int ID = 1;

public:
	Archer(OffsetCoords position, Player& owner);
	~Archer();
};

