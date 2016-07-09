#pragma once

#include <list>
#include "Page.h"
#include "Button.h"

#define NO_ITEM_SELECTED -1

class ComboButton : public Button
{
public:
	typedef Component ComboItem;
	typedef std::vector<ComboItem*> ItemContainer;
	typedef Event<Component> ExpandChange;

	ExpandChange& eventExpandChange() { return event_expand_change; }

	virtual void clicked(sf::Event::MouseButtonEvent& mouse);
	virtual void expandChange();
	virtual void focusChange();
	virtual void mouseEnter(sf::Event::MouseMoveEvent& args);
	virtual void mouseLeave(sf::Event::MouseMoveEvent& args);
	virtual void mouseMove(sf::Event::MouseMoveEvent& args);
	virtual void textEnter(sf::Event::TextEvent& args);

	virtual bool contains(sf::Vector2i vector);
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void refresh();

	void setExpanded(bool expanded);

	bool getExpanded() const { return expanded; }
	int32_t getItemCount() const { return item_count; }

	void addItem(ComboItem * item);
	void clear();

	ComboButton(std::string caption, sf::IntRect & position);
	ComboButton();
	~ComboButton();

private:
	ExpandChange event_expand_change;

	bool expanded;
	int expanded_length;
	int32_t item_count;
	Page items;
	int selected_item;

	void init();
};

