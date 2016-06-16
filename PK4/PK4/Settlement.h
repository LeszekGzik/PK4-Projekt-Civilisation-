#pragma once
#include "InGameObject.h"

class Settlement :
	public InGameObject
{
private:
	static const int TEX_ID;
	static const int TEXT_TOP;
	static const int CHAR_SIZE;

	static TexturedHex * style;

	int hardiness;
	int health;
	int strength;

	DrawableObject tile;
	sf::Text text;
	Tileset * tileset = nullptr;

	void setTextPosition();
public:
	static void setStyle(Hex * hex);
	static void clear();

	Settlement(AxialCoords position, Player& owner);
	~Settlement();

	Tileset * getTileset() const { return tileset; }

	void init();

	virtual CombatResult attacked(float strength, int & counter_damage) override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	virtual void move(AxialCoords coords) override;
	virtual void move(PixelCoords coords) override;
	virtual void newTurn() override;
	virtual void select(bool selected) override;
	virtual ContextInfoContent * getContextInfoContent() override;
};

