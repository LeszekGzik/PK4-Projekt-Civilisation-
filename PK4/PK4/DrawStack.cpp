#include "DrawStack.h"



void DrawStack::push(IDrawStack * object)
{
	DrawOrder order = object->getDrawOrder();

	if (hasFlag(order))
		return;

	setFlag(order);
	std::list<IDrawStack*>::iterator it = stack.begin();
	while (it != stack.end() && order < (*it)->getDrawOrder())
	{
		it++;
	}
	stack.insert(it, object);
}

void DrawStack::setFlag(DrawOrder flag)
{
	flags |= (1u << flag);
}

void DrawStack::clearFlag(DrawOrder flag)
{
	flags &= (1u << flag);
}

bool DrawStack::hasFlag(DrawOrder flag)
{
	return flags & _Pow_int(2, flag);
}


DrawStack::DrawStack()
{
}


DrawStack::~DrawStack()
{
}

void DrawStack::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (std::list<IDrawStack*>::const_reverse_iterator it = stack.rbegin(); it != stack.rend(); it++)
	{
		(*it)->draw(target, states);
	}
}
