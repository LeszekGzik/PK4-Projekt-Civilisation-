#include "Improvement.h"

const int Improvement::FLAG_ID = 2;

Improvement::Improvement(OffsetCoords position, Player & owner, int id) : id(id), InGameObject(position, owner)
{
	init();
}


Improvement::~Improvement()
{
}

void Improvement::init()
{
	this->ground = getStyle()->createGround(getPosition(), id);
	this->flag = getStyle()->createFlag(getPosition(), FLAG_ID, getOwner());
}

CombatResult Improvement::attacked(float strength, int & counter_damage)
{
	return CombatResult();
}

void Improvement::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(ground, states);
	target.draw(flag, states);
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
