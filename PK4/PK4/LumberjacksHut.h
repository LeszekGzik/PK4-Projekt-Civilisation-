#pragma once
#include "Improvement.h"
#include "TrainWorker.h"

class LumberjacksHut : public Improvement
{
private:
	int production = 1;

public:
	LumberjacksHut(Field * field, Player & owner);
	~LumberjacksHut();

	virtual void grantLoot(ResourcesHandler & handler);
	virtual void newTurn();
};

