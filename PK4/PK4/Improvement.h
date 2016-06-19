#pragma once
#include "InGameObject.h"

class Improvement : public InGameObject
{
private:
	static const int FLAG_ID;
	const int id;
	sf::Sprite ground;
	sf::Sprite flag;

public:
	Improvement(OffsetCoords position, Player & owner, int id);
	~Improvement();

	void init();

	// Inherited via InGameObject
	virtual CombatResult attacked(float strength, int & counter_damage);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void move(AxialCoords coords);
	virtual void move(PixelCoords coords);
	virtual void newTurn();
	virtual void select(bool selected);
	virtual ContextInfoContent * getContextInfoContent() { return nullptr; }
};

