#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Ability.h"
#include "EngineDefinitions.h"
#include "Player.h"
#include "ContextInfo.h"
#include "ObjectStyle.h"
#include "TexturedHex.h"

typedef std::vector<Ability*> Abilities;

class InGameObject : public sf::Drawable
{
private:
	static ObjectStyle * object_style;

	Abilities abilities;
	AxialCoords position;
	Player& owner;

public:
	static ObjectStyle * getStyle() { return object_style; }
	static void setStyle(ObjectStyle * style) { object_style = style; }
	static void setStyle(Hex * style);
	static void clear();

	InGameObject(AxialCoords position, Player& owner);
	virtual ~InGameObject();
	virtual CombatResult attacked(float strength, int & counter_damage) abstract;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const abstract;
	virtual void move(AxialCoords coords) abstract;
	virtual void move(PixelCoords coords) abstract;
	virtual void newTurn() abstract;
	virtual void select(bool selected) abstract;
	virtual void setOwner(Player & owner) { this->owner = owner; }
	virtual ContextInfoContent * getContextInfoContent() abstract;
	virtual Player & getOwner() { return owner; }

	virtual AxialCoords const& getPosition() const { return position; }
	virtual void setPosition(AxialCoords coords) { position = coords; }

	void grantAbility(Ability * ability);
};

