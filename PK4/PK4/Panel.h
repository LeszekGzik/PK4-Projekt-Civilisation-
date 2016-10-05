#pragma once
#include "Component.h"
#include "PageControl.h"

class Panel :
	public Component
{
public:
	virtual void clicked(sf::Event::MouseButtonEvent& mouse);
	virtual void mouseEnter(sf::Event::MouseMoveEvent& args);
	virtual void mouseLeave(sf::Event::MouseMoveEvent& args);
	virtual void mouseMove(sf::Event::MouseMoveEvent& args);
	virtual void textEnter(sf::Event::TextEvent& args);

	Panel();
	Panel(sf::IntRect position);
	~Panel();

	PageControl const& pageControl() { return this->page_control; }
	void addComponent(uint32_t index, Component * component);

private:
	PageControl page_control;
};

