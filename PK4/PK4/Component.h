#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Event.h"
#include "Fonts.h"

class Component : public sf::Drawable
{
public:
	typedef Event<Component, sf::Event::MouseButtonEvent> Clicked;
	typedef Event<Component, sf::Event::TextEvent> TextEnter;
	typedef Event<Component> FocusChange;
	typedef Event<Component, sf::Event::MouseMoveEvent> MouseEnter;
	typedef Event<Component, sf::Event::MouseMoveEvent> MouseLeave;

	Clicked& eventClicked() { return event_clicked; }
	FocusChange& eventFocusChange() { return event_focus_change; }
	TextEnter& eventTextEnter() { return event_text_enter; }
	MouseEnter& eventMouseEnter() { return event_mouse_enter; }
	MouseLeave& eventMouseLeave() { return event_mouse_leave; }
	virtual void clicked(sf::Event::MouseButtonEvent& mouse);
	virtual void focusChange();
	virtual void textEnter(sf::Event::TextEvent& args);
	virtual void mouseEnter(sf::Event::MouseMoveEvent& args);
	virtual void mouseLeave(sf::Event::MouseMoveEvent& args);

	void setBackColor(sf::Color color) { this->rectangle.setFillColor(color); }
	void setBorderColor(sf::Color color) { this->rectangle.setOutlineColor(color); }
	void setBorderThickness(float thickness) { this->rectangle.setOutlineThickness(thickness); }
	void setCaption(std::string caption) { this->text.setString(caption); }
	void setEnable(bool enabled) { this->enabled = enabled; }
	void setFocus(bool focused);
	void setFont(sf::Font& font) { this->text.setFont(font); }
	void setFontSize(int32_t size) { this->text.setCharacterSize(size); }
	void setPosition(sf::IntRect position) { this->position = position; }
	void setTextColor(sf::Color color) { this->text.setColor(color); }
	void setTextPosition(sf::Vector2u position) { this->text_position = position; }
	void setVisible(bool visible) { this->visible = visible; }

	std::string getCaption() { return this->text.getString().toAnsiString(); }
	bool getEnabled() { return this->enabled; }
	bool getFocused() { return this->focused; }
	sf::IntRect& getPosition() { return position; }
	bool getVisible() { return this->visible; }

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
	TextEnter event_text_enter;
	MouseEnter event_mouse_enter;
	MouseLeave event_mouse_leave;

	sf::IntRect position;
	sf::RectangleShape rectangle;
	sf::Text text;
	sf::Vector2u text_position; // relative to rectangle position

	bool focused = false;
	bool enabled = true;
	bool visible = true;

protected:
	const sf::RectangleShape & getRect() const { return rectangle; }
	const sf::Text & getText() const { return text; }
	void updateTextPosition() { text.setPosition(position.left + text_position.x, position.top + text_position.y); }
};

