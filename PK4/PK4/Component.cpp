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

void Component::focusChange()
{
	event_focus_change.invoke(*this);
}

void Component::keyDown(sf::Event::KeyEvent & args)
{
	event_key_down.invoke(*this, args);
}

void Component::setFocus(bool focused)
{
	this->focused = focused;
	focusChange();
}

void Component::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(rectangle, states);
	target.draw(text, states);
}

void Component::update()
{
	this->rectangle.setFillColor(this->back_color);
	this->text.setColor(this->text_color);
	this->text.setFont(this->font);
	this->text.setString(this->caption);
	this->rectangle.setPosition(position.left, position.top);
	this->rectangle.setSize(sf::Vector2f(position.width, position.height));

	updateTextPosition();
}


Component::Component() : font(Fonts::fontText())
{
}


Component::Component(std::string caption, sf::Color back_color, sf::Color border_color, sf::Color text_color, float border_thickness,
					 sf::Font & font, sf::Vector2u text_position, sf::IntRect position, int32_t font_size)
	: font(font)
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
