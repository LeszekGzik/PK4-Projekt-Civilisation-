#include "Unit.h"

ObjectStyle * Unit::object_style = NULL;

void Unit::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(token);
	target.draw(flag);
}

void Unit::move(AxialCoords coords)
{
	object_style->move(coords, token);
	object_style->move(coords, flag);
}

void Unit::move(PixelCoords coords)
{
	object_style->move(coords, token);
	object_style->move(coords, flag);
}

void Unit::select(bool selected)
{
	if (this->selected != selected)
	{
		this->selected = selected;
		sf::Color t_color = token.getColor();
		sf::Color f_color = flag.getColor();

		if (selected)
		{
			t_color.a = 160;
			f_color.a = 160;
		}
		else
		{
			t_color.a = 255;
			f_color.a = 255;
		}

		token.setColor(t_color);
		flag.setColor(f_color);
	}
}


void Unit::setStyle(TexturedHex * style)
{
	Hex * hex = style;
	object_style = new ObjectStyle(*hex);
}

Unit::Unit(int id, AxialCoords position, Player& owner) : owner(owner), id(id), InGameObject(position)
{
	flag = object_style->createFlag(position, id);
	token = object_style->createToken(position, id, owner);
}

Unit::~Unit()
{
}
