#pragma once
#include <SFML/Graphics.hpp>

enum DrawOrder
{
	Ground = 0,
	Structure = 1,
	Token = 2,
	Flag = 3
};

__interface IDrawStack 
{
	DrawOrder getDrawOrder();


	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states);

};
