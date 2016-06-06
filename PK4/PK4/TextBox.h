#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Component.h"

class TextBox : public Component
{
public:
	typedef Event<Component, std::string&> TextChange;

	TextChange& eventTextChange() { return event_text_change; }

	TextBox(std::string caption, sf::IntRect position);
	TextBox();
	~TextBox();

	virtual void focusChange();
	virtual void textEnter(sf::Event::TextEvent& args);

	void refresh();
	void setBackColor(sf::Color color);
	void setMaxLength(int32_t length) { this->max_length = length; }
	void setTextColor(sf::Color color);
	void setHighlightBackColor(sf::Color color) { this->highlight_back_color = color; }
	void setHighlightTextColor(sf::Color color) { this->highlight_text_color = color; }
	void setHighlights(bool enabled) { this->highlights = enabled; }

protected:
	virtual void highlightOn();
	virtual void highlightOff();

	void inputText(sf::Uint32 character);

private:
	TextChange event_text_change;

	bool caption_changed = false;
	sf::Color highlight_back_color;
	sf::Color highlight_text_color;
	sf::Color back_color;
	sf::Color text_color;
	int32_t max_length;
	std::string old_caption;

	bool highlighted;
	bool highlights;
};

