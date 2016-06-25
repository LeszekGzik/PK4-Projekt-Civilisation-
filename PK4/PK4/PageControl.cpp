#include "PageControl.h"


int PageControl::add()
{
	pages.push_back(new Page);
	return count++;
}

bool PageControl::click(sf::Event::MouseButtonEvent mouse)
{
	bool result = 0;
	for (auto i : this->merged_pages)
	{
		result += pages[i]->click(mouse);
		if (result)
			break;
	}
	return result;
}

bool PageControl::text(sf::Event::TextEvent key)
{
	bool result = 0;
	for (auto i : this->merged_pages)
	{
		result += pages[i]->text(key);
	}
	return result;
}

Page & PageControl::current()
{
	if (current_page < 0)
		throw IndexOutOfRangeException("PageControl", current_page);
	else
		return *pages[current_page];
}

bool PageControl::mouse(sf::Event::MouseMoveEvent mouse)
{
	bool result = 0;
	for (auto i : this->merged_pages)
	{
		result += pages[i]->mouse(mouse);
	}
	return result;
}

void PageControl::set(uint16_t index)
{
	if (index < count)
	{
		if (current_page >= 0) 
			current().leave();
		current_page = index;
		this->merged_pages.clear();
		merge(current_page);
	}
	else
		throw IndexOutOfRangeException("PageControl", index);
}

Page& PageControl::get(uint16_t index)
{
	if (index < count)
		return *pages[index];
	else
		throw IndexOutOfRangeException("PageControl", index);
}

void PageControl::merge(uint16_t index)
{
	if (index < count)
		this->merged_pages.insert(index);
	else
		throw IndexOutOfRangeException("PageControl", index);
}

void PageControl::remove(uint16_t index)
{
	if (index < count)
		this->merged_pages.erase(index);
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
	for (auto i : this->merged_pages)
	{
		target.draw(*pages[i], states);
	}
}
