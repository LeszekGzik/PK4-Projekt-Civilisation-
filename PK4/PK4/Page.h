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
	void click(sf::Event::MouseButtonEvent mouse);
	void keyDown(sf::Event::KeyEvent key);
	void mouse(sf::Event::MouseMoveEvent mouse);
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
	};

	CursorMarker mouse_cursor;
	ComponentList components;
	ShapeList shapes;
	Component * focused_component = NULL;

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

};