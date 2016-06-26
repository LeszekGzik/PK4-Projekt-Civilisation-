#pragma once
#include "Improvement.h"

class Farm : public Improvement
{
private:
	int production = 1;

public:
	Farm(Field* field, Player& owner);
	~Farm();

	void grantLoot(ResourcesHandler & handler);
	virtual void newTurn();
};

