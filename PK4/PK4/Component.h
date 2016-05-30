#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Event.h"
#include "Fonts.h"

class Component : public sf::Drawable
{
public:
	typedef Event<Component, sf::Event::MouseButtonEvent> Clicked;
	typedef Event<Component> FocusChange;
	typedef Event<Component, sf::Event::KeyEvent> KeyDown;
	typedef Event<Component, sf::Event::MouseMoveEvent> MouseEnter;
	typedef Event<Component, sf::Event::MouseMoveEvent> MouseLeave;

	Clicked& eventClicked() { return event_clicked; }
	FocusChange& eventFocusChange() { return event_focus_change; }
	KeyDown& eventKeyDown() { return event_key_down; }
	MouseEnter& eventMouseEnter() { return event_mouse_enter; }
	MouseLeave& eventMouseLeave() { return event_mouse_leave; }
	virtual void clicked(sf::Event::MouseButtonEvent& mouse);
	virtual void focusChange();
	virtual void keyDown(sf::Event::KeyEvent& args);
	virtual void mouseEnter(sf::Event::MouseMoveEvent& args);
	virtual void mouseLeave(sf::Event::MouseMoveEvent& args);

	sf::IntRect& getPosition() { return position; }
	void setBackColor(sf::Color color) { this->back_color = color; }
	void setBorderColor(sf::Color color) { this->rectangle.setOutlineColor(color); }
	void setBorderThickness(float thickness) { this->border_thickness = thickness; }
	void setCaption(std::string caption) { this->caption = caption; }
	void setFocus(bool focused);
	void setFont(sf::Font& font) { this->font = font; }
	void setFontSize(int32_t size) { this->text.setCharacterSize(size); }
	void setPosition(sf::IntRect position) { this->position = position; }
	void setTextColor(sf::Color color) { this->text_color = color; }
	void setTextPosition(sf::Vector2u position) { this->text_position = position; }

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void update();
	virtual void refresh() { }

	Component();
	Component(std::string caption, sf::Color back_color, sf::Color border_color, sf::Color text_color, float border_thickness,
		sf::Font& font, sf::Vector2u font_position, sf::IntRect position, int32_t font_size);
	~Component();

private:
	Clicked event_clicked;
	FocusChange event_focus_change;
	KeyDown event_key_down;
	MouseEnter event_mouse_enter;
	MouseLeave event_mouse_leave;

	sf::Color back_color;
	float border_thickness;
	std::string caption;
	sf::Font& font;
	sf::IntRect position;
	sf::RectangleShape rectangle;
	sf::Text text;
	sf::Color text_color;
	sf::Vector2u text_position; // relative to rectangle position

	bool focused = false;

protected:
	const sf::RectangleShape & getRect() const { return rectangle; }
	const sf::Text & getText() const { return text; }
	const sf::Font & getFont() const { return font; }
	void updateTextPosition() { text.setPosition(position.left + text_position.x, position.top + text_position.y); }
};

