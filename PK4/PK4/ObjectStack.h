#pragma once
#include <vector>
#include "InGameObject.h"
#include <SFML/Graphics.hpp>


class ObjectStack 
{
private:
	std::vector<InGameObject*> stack;

public:
	void add(InGameObject* object);

	ObjectStack();
	~ObjectStack();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

