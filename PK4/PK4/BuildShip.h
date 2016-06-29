#pragma once
#include "Ability.h"

class Ship;

class BuildShip :
	public Ability
{
public:
	BuildShip(InGameObject & owner);
	~BuildShip();

	virtual ContextInfoContent * getContextInfoContent();
	virtual void use();
};

#include "Ship.h"