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
	object_style->move(coords, getPosition(), token);
	object_style->move(coords, getPosition(), flag);
	setPosition(object_style->hex().toAxial(coords));
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

ContextInfoContent * Unit::getContextInfoContent()
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->push_back(ContextInfoLine(owner.getName(), ColorUtils::sfColor(owner.getColor())));
	vector->push_back(ContextInfoLine("HP: " + std::to_string(health), sf::Color(sf::Color::Black)));
	vector->push_back(ContextInfoLine("STR: " + std::to_string(strength), sf::Color(sf::Color::Black)));
	return vector;
}


void Unit::setStyle(TexturedHex * style)
{
	Hex * hex = style;
	object_style = new ObjectStyle(*hex);
}

void Unit::init()
{
	flag = object_style->createFlag(getPosition(), id);
	token = object_style->createToken(getPosition(), id, owner);
}

Unit::Unit(int id, AxialCoords position, Player& owner) : owner(owner), id(id), InGameObject(position)
{
	init();
}

Unit::Unit(int id, AxialCoords position, Player & owner, std::string const& name, int speed, int strength) 
	: owner(owner), id(id), name(name), speed(speed), strength(strength), InGameObject(position)
{
	init();
}

Unit::~Unit()
{
}
