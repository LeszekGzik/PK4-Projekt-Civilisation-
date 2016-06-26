#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Ability.h"
#include "EngineDefinitions.h"
#include "Player.h"
#include "ContextInfo.h"
#include "ObjectStyle.h"
#include "TexturedHex.h"
#include "Ability.h"

class Field;

typedef std::vector<Ability*> Abilities;

class InGameObject : public sf::Drawable
{
private:
	static ObjectStyle * object_style;

	Abilities abilities;
	Field * field;
	Player& owner;

public:
	const uint32_t max_movement_points = std::numeric_limits<uint32_t>::max();

	static ObjectStyle * getStyle() { return object_style; }
	static void setStyle(ObjectStyle * style) { object_style = style; }
	static void setStyle(Hex * style);
	static void clear();

	InGameObject(Field* field, Player& owner);
	virtual ~InGameObject();
	virtual CombatResult attacked(float strength, int & counter_damage) abstract;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const abstract;
	virtual void move(Field * destination) abstract;
	virtual void spendActionPoints(uint32_t points) abstract;
	void spendActionPoints() { spendActionPoints(max_movement_points); }
	virtual void newTurn() abstract;
	virtual void select(bool selected) abstract;
	virtual void setActionPoints(int points) abstract;
	virtual void setOwner(Player & owner) { this->owner = owner; }
	virtual void setField(Field *& field) { this->field = field; }
	virtual int getActionPoints() abstract;
	virtual ContextInfoContent * getContextInfoContent() abstract;
	virtual ContextInfoContent * getContextInfoContent(ContextInfoContent * content) abstract;
	virtual Player & getOwner() { return owner; }
	virtual Field *& getField() { return field; }

	template<typename TAbility> inline void grantAbility();
	Abilities const& getAbilities() const { return this->abilities; }
};

#include "Field.h"

template<typename TAbility>
inline void InGameObject::grantAbility()
{
	static_assert(std::is_base_of<Ability, TAbility>::value, "Input type must derive from Ability class");
	this->abilities.push_back(new TAbility(*this));
}
