#include "PageControl.h"


int PageControl::add()
{
	pages.push_back(new Page);
	return count++;
}

void PageControl::click(sf::Event::MouseButtonEvent mouse)
{
	current().click(mouse);
}

void PageControl::keyDown(sf::Event::KeyEvent key)
{
	current().keyDown(key);
}

Page & PageControl::current()
{
	if (current_page < 0)
		throw IndexOutOfRangeException("PageControl", current_page);
	else
		return *pages[current_page];
}

void PageControl::mouse(sf::Event::MouseMoveEvent mouse)
{
	current().mouse(mouse);
}

void PageControl::set(uint16_t index)
{
	if (index < count)
	{
		if (current_page > 0) 
			current().leave();
		current_page = index;
	}
	else
		throw IndexOutOfRangeException("PageControl", index);
}

PageControl::PageControl() : current_page(-1), count(0)
{
}

PageControl::~PageControl()
{
	for each (Page* page in pages)
	{
		delete page;
	}
}

void PageControl::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*pages[current_page], states);
}
