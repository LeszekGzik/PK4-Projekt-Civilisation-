#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "IDrawStack.h"
#include <cmath>

class DrawStack : sf::Drawable
{
private:
	std::list<IDrawStack*> stack;
	int flags = 0;

public:
	void push(IDrawStack * object);
	void setFlag(DrawOrder flag);
	void clearFlag(DrawOrder flag);
	bool hasFlag(DrawOrder flag);

	DrawStack();
	~DrawStack();

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

