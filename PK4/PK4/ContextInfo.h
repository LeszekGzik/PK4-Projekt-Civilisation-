#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "EngineDefinitions.h"

struct ContextInfoLine
{
	std::string string;
	sf::Color color;

	ContextInfoLine(std::string& string, sf::Color& color) : string(string), color(color)
	{ }
};

typedef std::vector<ContextInfoLine> ContextInfoContent;

class ContextInfo : public sf::Drawable
{
public:
	ContextInfo();
	~ContextInfo();

	void set(PixelCoords coords, ContextInfoContent content);	
	bool isActive() { return active; }
	void setActive(bool active) { this->active = active; }
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
	static const float TEXT_INTERVAL;
	static const int FONT_SIZE;
	static const sf::Color RECT_COLOR;

	sf::RectangleShape shape;
	sf::Text * lines;
	int32_t count;
	bool active = false;

	void initRect(PixelCoords coords, float height, float width);
};
