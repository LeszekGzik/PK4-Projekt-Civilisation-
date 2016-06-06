#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include "Component.h"
#include "GameExceptions.h"
#include "Page.h"

class PageControl : public sf::Drawable
{
public:
	typedef std::vector<Page*> PageContainer;

	int add();
	bool click(sf::Event::MouseButtonEvent mouse);
	bool text(sf::Event::TextEvent key);
	void mouse(sf::Event::MouseMoveEvent mouse);
	Page& current();
	void set(uint16_t index);

	PageControl();
	~PageControl();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
	PageContainer pages;
	int count;
	int current_page;

};

