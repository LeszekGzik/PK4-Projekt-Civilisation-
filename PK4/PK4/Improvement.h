#pragma once
#include "InGameObject.h"

class Field;

class Improvement : public InGameObject
{
private:
	static const int FLAG_ID;
	const int id;
	sf::Sprite ground;
	sf::Sprite flag;

	int action_points;
	int max_action_points;

public:
	Improvement(Field * field, Player & owner, int id, int max_action_points);
	~Improvement();

	void init();

	virtual CombatResult attacked(float strength, int & counter_damage);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void move(Field * destination);
	virtual void select(bool selected);
	virtual void spendActionPoints(uint32_t points);
	virtual void grantLoot(ResourcesHandler & handler) abstract;
	virtual void newTurn() { this->action_points = this->max_action_points; }
	virtual ContextInfoContent * getContextInfoContent() { return nullptr; }

	virtual int getActionPoints() { return this->action_points; }
	virtual void setActionPoints(int points) { this->action_points = points; }
};

