#pragma once

#include "Component.h"

class Button : public Component
{
public:
	Button();
	Button(std::string caption, sf::IntRect position);
	~Button();

	virtual void mouseEnter(sf::Event::MouseMoveEvent& args);
	virtual void mouseLeave(sf::Event::MouseMoveEvent& args);

	void refresh();
	void setBackColor(sf::Color color) { this->back_color = color; }
	void setTextColor(sf::Color color) { this->text_color = color; }
	void setHighlightBackColor(sf::Color color) { this->highlight_back_color = color; }
	void setHighlightTextColor(sf::Color color) { this->highlight_text_color = color; }
	void setHighlights(bool enabled) { this->highlights = enabled; }

protected:
	virtual void highlightOn();
	virtual void highlightOff();

private:
	sf::Color highlight_back_color;
	sf::Color highlight_text_color;
	sf::Color back_color;
	sf::Color text_color;

	bool highlighted;
	bool highlights;
};