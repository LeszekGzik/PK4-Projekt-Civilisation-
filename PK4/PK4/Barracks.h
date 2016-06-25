#pragma once
#include "Improvement.h"
#include "TrainArcher.h"

class Barracks :
	public Improvement
{
public:
	Barracks(Field * field, Player & owner);
	~Barracks();

	void grantLoot(ResourcesHandler & handler);
};

