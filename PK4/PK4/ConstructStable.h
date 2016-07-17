#pragma once
#include "Ability.h"

class Stable;

class ConstructStable :
	public Ability
{
public:
	ConstructStable(InGameObject & owner);
	~ConstructStable();

	virtual ContextInfoContent * getContextInfoContent();
	virtual void use(Field * target = nullptr);
};

#include "Stable.h"

