#pragma once
#include "Improvement.h"

class Farm : public Improvement
{
private:

public:
	Farm(Field* field, Player& owner);
	~Farm();

	void grantLoot(ResourcesHandler & handler);
};

