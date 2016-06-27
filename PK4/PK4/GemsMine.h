#pragma once
#include "Improvement.h"
#include "TrainWorker.h"

class GemsMine :
	public Improvement
{
private:
	int production = 1;
public:
	GemsMine(Field * field, Player & owner);
	~GemsMine();

	virtual void grantLoot(ResourcesHandler & handler);
	virtual void newTurn();
};

