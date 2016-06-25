#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include <string>
#include "Event.h"
#include "ContextInfo.h"

class InGameObject;

class Ability
{
public:
	Ability(uint32_t texture_id, InGameObject& owner);
	~Ability();

	uint16_t getTextureId() const { return this->texture_id; }
	sf::IntRect const& getTextureTile() const { return Textures::tilesetButtons().getTile(this->texture_id); }
	InGameObject & getOwner() { return this->owner; }
	virtual ContextInfoContent * getContextInfoContent() abstract;
	virtual void use() abstract;

private:
	uint32_t texture_id;
	InGameObject& owner;
};

#include "InGameObject.h"