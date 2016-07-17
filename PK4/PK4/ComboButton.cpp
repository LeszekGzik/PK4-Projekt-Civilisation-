#include "ComboButton.h"

void ComboButton::clicked(sf::Event::MouseButtonEvent & mouse)
{
	Component * base = this;
	if (expanded)
	{
		bool received = items.click(mouse);
		if (received)
		{
			setExpanded(false);
		}
	}
	else
	{
		base->eventClicked().invoke(*this, mouse);
		setExpanded(true);
	}
}

void ComboButton::expandChange()
{
	event_expand_change.invoke(*this);
	if (!expanded)
	{
		this->selected_item = NO_ITEM_SELECTED;
		items.leave();
	}
}


bool ComboButton::contains(sf::Vector2i vector)
{
	sf::IntRect temp = getPosition();
	if (this->expanded)
		temp.height += this->expanded_length;
	return temp.contains(vector);
}

void ComboButton::focusChange()
{
	eventFocusChange().invoke(*this);
	if (!getFocused())
		setExpanded(false);
}

void ComboButton::mouseEnter(sf::Event::MouseMoveEvent & args)
{
	eventMouseEnter().invoke(*this, args);
	if (getHighlights())
		highlightOn();
}

void ComboButton::mouseLeave(sf::Event::MouseMoveEvent & args)
{
	eventMouseLeave().invoke(*this, args);
	if (getHighlights())
		highlightOff();
	items.mouse(args);
}

void ComboButton::mouseMove(sf::Event::MouseMoveEvent & args)
{
	eventMouseMove().invoke(*this, args);
	items.mouse(args);
}

void ComboButton::textEnter(sf::Event::TextEvent & args)
{
	eventTextEnter().invoke(*this, args);
	ComboItem * item = items.focused();
	if (item != NULL)
		item->textEnter(args);
}

void ComboButton::addItem(ComboItem * item)
{
	sf::IntRect btn_pos = getPosition();
	sf::IntRect item_pos = item->getPosition();

	
	item->setPosition(sf::IntRect(btn_pos.left, this->expanded_length + btn_pos.top + btn_pos.height, btn_pos.width, item_pos.height));
	item->update();
	this->expanded_length += item_pos.height;

	items.addComponent(item);
	item_count++;
}

void ComboButton::clear()
{
	item_count = 0;
	expanded_length = 0;
	items.clear();
}

void ComboButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (getVisible())
	{
		target.draw(getRect(), states);
		target.draw(getText(), states);

		if (this->expanded)
		{
			target.draw(items, states);
		}
	}
}

void ComboButton::refresh()
{
	expanded = false;
}

void ComboButton::setExpanded(bool expanded)
{
	if (this->expanded != expanded)
	{
		this->expanded = expanded;
		expandChange();
	}
}


ComboButton::ComboButton(std::string caption, sf::IntRect & position) : Button(caption, position)
{
	init();
}


ComboButton::ComboButton()
{
	init();
}


ComboButton::~ComboButton()
{
}

void ComboButton::init()
{
	this->setExpanded(false);
	this->expanded_length = 0;
	this->selected_item = NO_ITEM_SELECTED;
}
