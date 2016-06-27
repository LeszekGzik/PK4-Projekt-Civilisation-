#pragma once
#include "Field.h"
#include "DepositExtension.h"

class Hills :
	public Field, public DepositExtension
{
public:
	Hills(OffsetCoords position);
	~Hills();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};


