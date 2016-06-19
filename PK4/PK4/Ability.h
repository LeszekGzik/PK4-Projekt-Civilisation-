#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include <string>

class Ability
{
public:
	Ability(uint32_t texture_id, std::string description);
	~Ability();

	sf::IntRect const& getTextureTile() const { return Textures::tilesetButtons().getTile(this->texture_id); }
	std::string const& getDescription() const { return this->description; }

	virtual void use() abstract;

private:
	uint32_t texture_id;
	std::string description;
};

