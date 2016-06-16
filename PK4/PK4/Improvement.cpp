#include "Improvement.h"

Improvement::Improvement(OffsetCoords position, Player & owner, int id) : id(id), InGameObject(position, owner)
{
	init();
}


Improvement::~Improvement()
{
}

void Improvement::init()
{
	this->sprite = getStyle()->createGround(getPosition(), id);
}

CombatResult Improvement::attacked(float strength, int & counter_damage)
{
	return CombatResult();
}

void Improvement::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void Improvement::move(AxialCoords coords)
{
}

void Improvement::move(PixelCoords coords)
{
}

void Improvement::newTurn()
{
}

void Improvement::select(bool selected)
{
}
