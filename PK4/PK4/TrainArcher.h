#pragma once
#include "Ability.h"

class Archer;

class TrainArcher :
	public Ability
{
public:
	TrainArcher(InGameObject & owner);
	~TrainArcher();

	virtual ContextInfoContent * getContextInfoContent();
	virtual void use(Field * target = nullptr);
};

#include "Archer.h"
