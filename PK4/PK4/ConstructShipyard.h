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
	virtual ContextInfoContent * getContextInfoContent() override;
	virtual void use() override;
};

#include "Shipyard.h"