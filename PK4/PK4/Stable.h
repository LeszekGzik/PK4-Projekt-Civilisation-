#pragma once
#include "Improvement.h"
class Stable :
	public Improvement
{
public:
	Stable(Field * field, Player & owner);
	~Stable();

	virtual void grantLoot(ResourcesHandler & handler) override;
};

