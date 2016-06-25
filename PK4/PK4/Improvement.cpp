#include "Improvement.h"

const int Improvement::FLAG_ID = 2;

Improvement::Improvement(Field* field, Player & owner, int id, int max_action_points) 
	: id(id), max_action_points(max_action_points), InGameObject(field, owner)
{
	init();
}


Improvement::~Improvement()
{
}

void Improvement::init()
{
	OffsetCoords & position = getField()->getPosition();
	this->ground = getStyle()->createGround(position, id);
	this->flag = getStyle()->createFlag(position, FLAG_ID, getOwner());
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

void Improvement::move(Field * destination)
{
}

void Improvement::select(bool selected)
{
}

void Improvement::spendActionPoints(uint32_t points)
{
	if (points == max_action_points)
		this->action_points = 0;
	else
		this->action_points -= points;
}
