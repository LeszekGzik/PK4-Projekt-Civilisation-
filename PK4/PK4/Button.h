#pragma once

#include "Component.h"
#include "Tileset.h"

enum DisplayStyle { Text, Image };

class Button : public Component
{
public:
	Button();
	Button(std::string caption, sf::IntRect position);
	~Button();

	virtual void mouseEnter(sf::Event::MouseMoveEvent& args);
	virtual void mouseLeave(sf::Event::MouseMoveEvent& args);

	virtual DisplayStyle getDisplayStyle() { return this->display_style; }
	virtual sf::Sprite getImage() const { return this->image; }
	virtual void setDisplayStyle(DisplayStyle style) { this->display_style = style; }
	virtual void setImage(Tileset& tileset, int32_t tile);

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	void refresh();
	void setBackColor(sf::Color color);
	void setTextColor(sf::Color color);
	void setHighlightBackColor(sf::Color color) { this->highlight_back_color = color; }
	void setHighlightTextColor(sf::Color color) { this->highlight_text_color = color; }
	void setHighlights(bool enabled) { this->highlights = enabled; }

	bool getHighlights() const { return this->highlights; }

protected:
	virtual void highlightOn();
	virtual void highlightOff();

private:
	sf::Sprite image;

	sf::Color highlight_back_color;
	sf::Color highlight_text_color;
	sf::Color back_color;
	sf::Color text_color;

	DisplayStyle display_style;
	bool highlighted;
	bool highlights;
};