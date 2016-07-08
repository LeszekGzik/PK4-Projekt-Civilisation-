#pragma once
#include "Ability.h"

class Forest;
class LumberjacksHut;

class ConstructLumberjacksHut :
	public Ability
{
public:
	ConstructLumberjacksHut(InGameObject& owner);
	~ConstructLumberjacksHut();

	virtual ContextInfoContent * getContextInfoContent();
	virtual void use(Field * target = nullptr);
};

#include "LumberjacksHut.h"
#include "Forest.h"