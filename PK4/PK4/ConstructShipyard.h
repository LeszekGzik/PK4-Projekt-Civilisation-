#pragma once
#include "Ability.h"

class Shipyard;

class ConstructShipyard :
	public Ability
{
public:
	ConstructShipyard(InGameObject & owner);
	~ConstructShipyard();

	// Inherited via Ability
	virtual ContextInfoContent * getContextInfoContent();
	virtual void use(Field * target = nullptr);
};

#include "Shipyard.h"