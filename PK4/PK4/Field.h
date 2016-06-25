#pragma once
#include <SFML/Graphics.hpp>
#include "EngineDefinitions.h"
#include "ContextInfo.h"
#include "TexturedHex.h"
#include "Textures.h"
#include "Player.h"
#include "ObjectStack.h"

class Improvement;

class Field : public sf::Drawable
{
private:
	int id;
	int movement_cost;
	FieldType type;
	ObjectStack object_stack;
	Improvement * improvement = nullptr;
	DrawableObject vertex;
	OffsetCoords position;

	static TexturedHex * hex_style;

public:

	static Tileset tileset() { return Textures::tilesetFields(); }
	static void setStyle(TexturedHex * style) { Field::hex_style = style; }

	template <typename TUnit> inline void newUnit(Player& owner);
	template <typename TImp> inline void newImprovement(Player& owner);
	void deleteImprovement();

	ObjectStack & objects() { return object_stack; }
	OffsetCoords & getPosition() { return position; }
	int getMovementCost() const { return this->movement_cost; }
	FieldType getType() const { return this->type; }
	Improvement * getImprovement() { return this->improvement; }

	void setImprovement(Improvement * imp) { this->improvement = imp; }

	Field(int id, OffsetCoords position, int movement_cost, FieldType type);
	~Field();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void newTurn();
	ContextInfoContent * getContextInfoContent();
};
	
template<typename TUnit>
inline void Field::newUnit(Player & owner)
{
	static_assert(std::is_base_of<Unit, TUnit>::value, "Input type must derive from Unit class");
	this->object_stack.add(new TUnit(this, owner));
}

template<typename TImp>
inline void Field::newImprovement(Player & owner)
{
	//static_assert(std::is_base_of<Improvement, TImp)::value, "Input type must derive from Improvement class");
	improvement = new TImp(this, owner);
}

#include "Improvement.h"