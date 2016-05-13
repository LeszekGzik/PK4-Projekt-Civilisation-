#include "ObjectStack.h"



void ObjectStack::add(InGameObject * object)
{
	stack.push_back(object);
}

ObjectStack::ObjectStack()
{
}


ObjectStack::~ObjectStack()
{
}

void ObjectStack::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	size_t i = stack.size();

	if (i != 0)
	{
		do
		{
			i--;
			target.draw(*stack[i]);
			if (stack[i]->coversStack())
				break;
		} while (i != 0);
	}
}
