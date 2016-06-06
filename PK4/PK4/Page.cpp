#include "Page.h"

Page::Page()
{
	mouse_cursor.is_valid = false;
}

Page::~Page()
{
	for each (Component* obj in components)
	{
		delete obj;
	}
	for each (sf::Shape* obj in shapes)
	{
		delete obj;
	}
}

void Page::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for each (sf::Shape* obj in shapes)
	{
		target.draw(*obj, states);
	}
	for each (Component* obj in components)
	{
		target.draw(*obj, states);
	}
}

void Page::addComponent(Component * item)
{
	components.push_back(item);
}

void Page::addShape(sf::Shape * item)
{
	shapes.push_back(item);
}

bool Page::click(sf::Event::MouseButtonEvent mouse)
{
	bool processed = false;

	sf::Vector2i click(mouse.x, mouse.y);
	ComponentList::iterator it = std::find_if(components.begin(), components.end(), [&click](Component*& o) { return o->contains(click); });
	if (it != components.end())
	{
		if (focused_component != NULL && focused_component != (*it))
			focused_component->setFocus(false);
		if ((*it)->getEnabled())
		{
			focused_component = *it;
			focused_component->setFocus(true);
			(*it)->clicked(mouse);
		}
		processed = true;
	}
	else if (focused_component != NULL)
	{
		focused_component->setFocus(false);
		focused_component = NULL;
	}
	return processed;
}

bool Page::text(sf::Event::TextEvent key)
{
	if (focused_component != NULL && focused_component->getFocused())
	{
		focused_component->textEnter(key);
		return true;
	}
	return false;
}

bool Page::mouse(sf::Event::MouseMoveEvent mouse)
{
	sf::Vector2i pos(mouse.x, mouse.y);
	ComponentList::iterator it = std::find_if(components.begin(), components.end(), [&pos](Component*& o) { return o->contains(pos); });
	
	if (mouse_cursor.is_valid && mouse_cursor != it && (*mouse_cursor)->getEnabled())
		(*mouse_cursor)->mouseLeave(mouse);

	if (it != components.end() && (*it)->getEnabled())
	{
		if (mouse_cursor != it)
		{
			mouse_cursor = it;
			(*mouse_cursor)->mouseEnter(mouse);
		}
		(*it)->mouseMove(mouse);
		return true;
	}
	else
	{
		mouse_cursor.is_valid = false;
		return false;
	}
		
}

void Page::leave()
{
	mouse_cursor.is_valid = false;
	if (focused_component != NULL)
	{
		focused_component->setFocus(false);
		focused_component = NULL;
	}
}

void Page::refresh()
{
	for each(Component* item in components)
	{
		item->refresh();
	}
}

