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

	Component * focused() { return focused_component; }

	Page();
	~Page();

private:
	struct CursorMarker : ComponentList::iterator
	{
		bool is_valid;
		CursorMarker& operator= (ComponentList::iterator obj)
		{
			ComponentList::iterator * base = this;
			*base = obj;
			this->is_valid = true;
			return *this;
		}

		Component* & operator* ()
		{
			ComponentList::iterator * base = this;
			return **base;
		}

		bool operator== (ComponentList::iterator const& arg) 
		{
			if (!is_valid)
				return false;
			else
			{
				ComponentList::iterator * base = this;
				return (arg == *this);
			}
		}

		bool operator != (ComponentList::iterator const& arg)
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