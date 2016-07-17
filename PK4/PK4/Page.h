#pragma once
#include <SFML\Graphics.hpp>
#include <list>
#include <iterator>
#include "Component.h"

class Page : public sf::Drawable
{
public:
	typedef std::list<Component*> ComponentList;
	typedef std::list<sf::Shape*> ShapeList;

	void addComponent(Component* item);
	void addShape(sf::Shape* item);
	bool click(sf::Event::MouseButtonEvent mouse);
	bool text(sf::Event::TextEvent key);
	bool mouse(sf::Event::MouseMoveEvent mouse);
	void leave();
	void refresh();
	void clear();

	Component * focused() { return focused_component; }

	Page();
	~Page();

private:
	struct CursorMarker : ComponentList::reverse_iterator
	{
		bool is_valid;
		CursorMarker& operator= (ComponentList::reverse_iterator obj)
		{
			ComponentList::reverse_iterator * base = this;
			*base = obj;
			this->is_valid = true;
			return *this;
		}

		Component* & operator* ()
		{
			ComponentList::reverse_iterator * base = this;
			return **base;
		}

		bool operator== (ComponentList::reverse_iterator const& arg)
		{
			if (!is_valid)
				return false;
			else
			{
				ComponentList::reverse_iterator * base = this;
				return (arg == *this);
			}
		}

		bool operator != (ComponentList::reverse_iterator const& arg)
		{
			return !(*this == arg);
		}
	};

	CursorMarker mouse_cursor;
	ComponentList components;
	ShapeList shapes;
	Component * focused_component = NULL;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

};