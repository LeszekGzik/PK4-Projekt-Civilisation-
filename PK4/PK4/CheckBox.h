#pragma once
#include "Component.h"
#include "Textures.h"

class CheckBox :
	public Component
{
public:
	CheckBox();
	CheckBox(std::string & caption, sf::IntRect & bounds);
	~CheckBox();

	virtual void clicked(sf::Event::MouseButtonEvent&);

	bool isChecked() { return this->checked; }

private:
	static const int UNCHECKED = 1;
	static const int CHECKED = 2;

	bool checked;
	sf::Sprite box;
	Tileset & tileset = Textures::tilesetCheckbox();

	void init();
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};

