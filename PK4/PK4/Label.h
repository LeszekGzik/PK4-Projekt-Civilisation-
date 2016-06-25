#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Component.h"
#include "Textures.h"

class Label : public Component
{
public:
	Label(std::string caption, sf::IntRect position);
	Label();
	~Label();

	virtual DisplayStyle getDisplayStyle() { return this->display_style; }
	virtual sf::Sprite getImage() const { return this->image; }
	virtual void setDisplayStyle(DisplayStyle style) 
	{ 
		this->display_style = style; 
	}
	virtual void setImage(Tileset& tileset, uint32_t tile);

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

private:
	DisplayStyle display_style;
	sf::Sprite image;
};

