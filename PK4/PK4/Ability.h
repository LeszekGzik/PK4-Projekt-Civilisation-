#pragma once
#include <SFML/Graphics.hpp>
#include "Textures.h"
#include <string>
#include "Event.h"
#include "ContextInfo.h"

#define _targetable true
#define _not_targetable false

class InGameObject;
class Field;

class Ability
{
public:
	Ability(uint32_t texture_id, InGameObject& owner, bool targetable);
	~Ability();

	bool isTargetable() const { return targetable; }
	uint16_t getTextureId() const { return this->texture_id; }
	sf::IntRect const& getTextureTile() const { return Textures::tilesetButtons().getTile(this->texture_id); }
	InGameObject & getOwner() { return this->owner; }
	virtual ContextInfoContent * getContextInfoContent() abstract;
	virtual void use(Field * target = nullptr) abstract;

private:
	bool targetable;
	uint32_t texture_id;
	InGameObject& owner;
};

#include "InGameObject.h"