#include "Improvement.h"

const int Improvement::FLAG_ID = 2;

Improvement::Improvement(Field* field, Player & owner, std::string const& name, int id, int max_action_points) 
	: id(id), name(name), max_action_points(max_action_points), InGameObject(field, owner)
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
	this->selection = getStyle()->hex().create(position, ColorUtils::sfColor(getOwner().getColor()));
}

CombatResult Improvement::attacked(float strength, int & counter_damage)
{
	return CombatResult();
}

void Improvement::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->flag, states);
	target.draw(this->ground, states);
	if (this->selected)
		target.draw(this->selection);
}

void Improvement::move(Field * destination)
{
}

void Improvement::select(bool selected)
{
	this->selected = selected;
}

void Improvement::spendActionPoints(uint32_t points)
{
	if (points == max_action_points)
		this->action_points = 0;
	else
		this->action_points -= points;
}

ContextInfoContent * Improvement::getContextInfoContent()
{
	return getContextInfoContent(new ContextInfoContent);
}

ContextInfoContent * Improvement::getContextInfoContent(ContextInfoContent * vector)
{
	vector->emplace_back(getOwner().getName(), ColorUtils::sfColor(getOwner().getColor()));
	vector->emplace_back(name, sf::Color::Black);
	return vector;
}
