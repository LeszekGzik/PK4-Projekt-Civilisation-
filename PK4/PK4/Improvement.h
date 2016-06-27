#pragma once
#include "InGameObject.h"

class Field;

class Improvement : public InGameObject
{
private:
	static const int FLAG_ID;
	const int id;
	bool selected;
	sf::Sprite ground;
	sf::Sprite flag;
	DrawableObject selection;

	int action_points;
	int max_action_points;
	std::string name;
	

public:
	Improvement(Field * field, Player & owner, std::string const& name, int id, int max_action_points);
	~Improvement();

	void init();

	virtual CombatResult attacked(float strength, int & counter_damage);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void move(Field * destination);
	virtual void select(bool selected);
	virtual void spendActionPoints(uint32_t points);
	virtual void grantLoot(ResourcesHandler & handler) abstract;
	virtual void newTurn() { this->action_points = this->max_action_points; }
	virtual ContextInfoContent * getContextInfoContent();
	virtual ContextInfoContent * getContextInfoContent(ContextInfoContent * content);

	virtual int getActionPoints() { return this->action_points; }
	virtual int getMaxActionPoints() { return this->max_action_points; }
	virtual void setActionPoints(int points) { this->action_points = points; }
	virtual void setMaxActionPoints(int max_points) { this->max_action_points = max_points; }

	virtual bool canAttack() { return false; }
	virtual bool hasFullAction() { return this->max_movement_points == this->action_points; }
};

