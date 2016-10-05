#include "Panel.h"

namespace
{
	const sf::Color BACK_COLOR(255, 255, 255, 0);
	const sf::Color BORDER_COLOR(255, 255, 255, 255);
	const float BORDER_THICKNESS = 0;
}

void Panel::clicked(sf::Event::MouseButtonEvent & mouse)
{
	bool handled = this->page_control.click(mouse);
	if (!handled)
		eventClicked().invoke(*this, mouse);
}

void Panel::mouseEnter(sf::Event::MouseMoveEvent & args)
{
	bool handled = this->page_control.mouse(args);
	if (!handled)
		eventMouseEnter().invoke(*this, args);
}

void Panel::mouseLeave(sf::Event::MouseMoveEvent & args)
{
	bool handled = this->page_control.mouse(args);
	if (!handled)
		eventMouseLeave().invoke(*this, args);
}

void Panel::mouseMove(sf::Event::MouseMoveEvent & args)
{
	bool handled = this->page_control.mouse(args);
	if (!handled)
		eventMouseMove().invoke(*this, args);
}

void Panel::textEnter(sf::Event::TextEvent & args)
{
	bool handled = this->page_control.text(args);
	if (!handled)
		eventTextEnter().invoke(*this, args);
}

Panel::Panel()
{
}

Panel::Panel(sf::IntRect position)
{
	setBackColor(BACK_COLOR);
	setBorderColor(BORDER_COLOR);
	setBorderThickness(BORDER_THICKNESS);
}

Panel::~Panel()
{
}

void Panel::addComponent(uint32_t index, Component * component)
{
	sf::IntRect container_position = getPosition();
	sf::IntRect absolute_position = component->getPosition();

	absolute_position.left += container_position.left;
	absolute_position.top += container_position.top;

	component->setPosition(absolute_position);

	this->page_control.get(index).addComponent(component);
}
