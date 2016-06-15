#pragma once
#include <SFML/Graphics.hpp>
#include "EngineDefinitions.h"
#include "ContextInfo.h"
#include "ObjectStack.h"
#include "TexturedHex.h"
#include "Textures.h"
#include "Improvement.h"
#include "Player.h"

class Field : public sf::Drawable
{
private:
	int id;
	int movement_cost;
	FieldType type;
	ObjectStack object_stack;
	Improvement improvement;
	DrawableObject vertex;
	OffsetCoords position;

	static TexturedHex * hex_style;

public:

	static Tileset tileset() { return Textures::tilesetFields(); }
	static void setStyle(TexturedHex * style) { Field::hex_style = style; }

	template <typename TUnit> inline void newObject(Player& owner);

	ObjectStack & objects() { return object_stack; }
	OffsetCoords & getPosition() { return position; }
	int getMovementCost() const { return this->movement_cost; }
	FieldType getType() const { return this->type; }

	Field(int id, OffsetCoords position, int movement_cost, FieldType type);
	~Field();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void newTurn();
	ContextInfoContent * getContextInfoContent();
};

template<typename TUnit>
inline void Field::newObject(Player & owner)
{
	TUnit * unit = new TUnit(position, owner);
	object_stack.add(unit);
}
