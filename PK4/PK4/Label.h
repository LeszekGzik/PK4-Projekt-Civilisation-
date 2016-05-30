#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Component.h"

class Label : public Component
{
public:
	Label(std::string caption, sf::IntRect position);
	Label();
	~Label();
};

