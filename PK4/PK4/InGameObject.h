#pragma once
#include <SFML\Graphics.hpp>
#include "EngineDefinitions.h"
#include "ContextInfo.h"

class InGameObject : public sf::Drawable
{
private:
	AxialCoords position;

public:
	InGameObject(AxialCoords position);
	virtual ~InGameObject();
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const abstract;
	virtual void move(AxialCoords coords) abstract;
	virtual void move(PixelCoords coords) abstract;
	virtual void select(bool selected) abstract;
	virtual ContextInfoContent getContextInfoContent() abstract;

	virtual AxialCoords const& getPosition() const { return position; }
	virtual void setPosition(AxialCoords coords) { position = coords; }
};

