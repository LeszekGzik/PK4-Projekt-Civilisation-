#include "Component.h"


void Component::clicked(sf::Event::MouseButtonEvent & mouse)
{
	event_clicked.invoke(*this, mouse);
}

void Component::mouseEnter(sf::Event::MouseMoveEvent& args)
{
	event_mouse_enter.invoke(*this, args);
}

void Component::mouseLeave(sf::Event::MouseMoveEvent & args)
{
	event_mouse_leave.invoke(*this, args);
}

void Component::mouseMove(sf::Event::MouseMoveEvent & args)
{
	event_mouse_move.invoke(*this, args);
}

void Component::focusChange()
{
	event_focus_change.invoke(*this);
}

void Component::textEnter(sf::Event::TextEvent & args)
{
	event_text_enter.invoke(*this, args);
}

void Component::setFocus(bool focused)
{
	if (focused != this->focused)
	{
		this->focused = focused;
		focusChange();
	}
}

bool Component::contains(sf::Vector2i vector)
{
	return position.contains(vector);
}

void Component::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (visible)
	{
		target.draw(rectangle, states);
		target.draw(text, states);
	}
}

void Component::update()
{
	this->rectangle.setPosition(position.left, position.top);
	this->rectangle.setSize(sf::Vector2f(position.width, position.height));

	updateTextPosition();
}


Component::Component()
{
}


Component::Component(std::string caption, sf::Color back_color, sf::Color border_color, sf::Color text_color, float border_thickness,
					 sf::Font & font, sf::Vector2u text_position, sf::IntRect position, int32_t font_size)
{
	setCaption(caption);
	setBackColor(back_color);
	setBorderColor(border_color);
	setBorderThickness(border_thickness);
	setFont(font);
	setFontSize(font_size);
	setPosition(position);
	setTextColor(text_color);
	setTextPosition(text_position);
	update();
}

Component::~Component()
{
}
