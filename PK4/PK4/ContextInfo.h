#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "EngineDefinitions.h"
#include "Fonts.h"

struct ContextInfoLine
{
	std::string string;
	sf::Color color;

	ContextInfoLine(const std::string & string, const sf::Color & color) : string(string), color(color)
	{ }

	static ContextInfoLine empty()
	{
		return ContextInfoLine(std::string(" "), sf::Color(sf::Color::Transparent));
	}
};

typedef std::vector<ContextInfoLine> ContextInfoContent;

class ContextInfo : public sf::Drawable
{
public:
	enum Aligment { Down = 1, Up = -1 };

	ContextInfo();
	~ContextInfo();

	void set(PixelCoords coords, ContextInfoContent * content);	
	bool isActive() { return active; }
	Aligment getAligment(Aligment aligment) { return this->aligment; }
	void setActive(bool active) { this->active = active; }
	void setAligment(Aligment aligment) { this->aligment = aligment; }
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
	static const float CURSOR_OFFSET;
	static const float TEXT_INTERVAL;
	static const float RECT_OFFSET_VERTICAL;
	static const float RECT_OFFSET_HORIZONTAL;
	static const int FONT_SIZE;
	static const sf::Color RECT_COLOR;

	sf::RectangleShape shape;
	sf::Text * lines;
	int32_t count;
	Aligment aligment;

	bool active = false;
	float line_height;

	void initRect(PixelCoords coords, float height, float width);
	void update();
};
