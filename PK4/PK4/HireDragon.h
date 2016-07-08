#pragma once
#include "Ability.h"

class Dragon;

class HireDragon :
	public Ability
{
public:
	HireDragon(InGameObject & owner);
	~HireDragon();

	virtual ContextInfoContent * getContextInfoContent();
	virtual void use(Field * target = nullptr);
};

#include "Dragon.h"