#pragma once
#include "Improvement.h"
#include "TrainWorker.h"

class IronMine :
	public Improvement
{
private:
	int production = 1;

public:
	IronMine(Field * field, Player & owner);
	~IronMine();

	virtual void grantLoot(ResourcesHandler & handler);
	virtual void newTurn();
};

