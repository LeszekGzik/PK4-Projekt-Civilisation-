#pragma once
#include <SFML\Graphics.hpp>

class InGameObject : public sf::Drawable
{
private:
	bool covers_stack;
	
public:
	InGameObject();
	bool coversStack();
	virtual ~InGameObject();
};

