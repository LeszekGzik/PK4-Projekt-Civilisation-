#pragma once
#include <SFML\Graphics.hpp>

class InGameObject : public sf::Drawable
{
private:
	
public:
	InGameObject();
	virtual ~InGameObject();
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) abstract;
};

