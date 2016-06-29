#pragma once
#include "Improvement.h"
#include "BuildShip.h"

class Shipyard :
	public Improvement
{
public:
	Shipyard(Field * field, Player & owner);
	~Shipyard();

	void grantLoot(ResourcesHandler & handler);
};

