#include "Unit.h"

namespace
{
	const int TOKEN_ID = 1;
}

void Unit::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(token);
	target.draw(banner);
}

/*void Unit::move(AxialCoords coords)
{
	ObjectStyle * style = getStyle();
	PixelCoords pixels = style->hex().toPixel(coords);
	pixels.x += style->hex().horizontalSize() / 2;
	pixels.y += style->hex().verticalSize() / 2;
	//move(pixels);
}*/

void Unit::move(Field * destination)
{
	ObjectStyle * style = getStyle();
	Field *& field = getField();
	PixelCoords coords = style->hex().toPixel(destination->getPosition());
	coords.x += style->hex().horizontalSize() / 2;
	coords.y += style->hex().verticalSize() / 2;
	style->move(coords, field->getPosition(), token);
	style->move(coords, field->getPosition(), banner);
	destination->objects().add(this);
	setField(destination);
}

void Unit::newTurn()
{
	movement_points = speed;
	attacked_this_turn = false;
}

void Unit::select(bool selected)
{
	if (this->selected != selected)
	{
		this->selected = selected;
		sf::Color t_color = token.getColor();
		sf::Color f_color = banner.getColor();

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
		banner.setColor(f_color);
	}
}

ContextInfoContent * Unit::getContextInfoContent()
{
	return getContextInfoContent(new ContextInfoContent);
}

ContextInfoContent * Unit::getContextInfoContent(ContextInfoContent * content)
{
	ContextInfoContent * vector = new ContextInfoContent();
	vector->push_back(ContextInfoLine(getOwner().getName(), ColorUtils::sfColor(getOwner().getColor())));
	vector->push_back(ContextInfoLine("HP: " + std::to_string(health), sf::Color::Black));
	vector->push_back(ContextInfoLine("STR: " + std::to_string(strength), sf::Color::Black));
	vector->push_back(ContextInfoLine("MOVE: " + std::to_string(movement_points) + "/" + std::to_string(speed), sf::Color(sf::Color::Black)));
	return vector;
}

void Unit::init()
{
	OffsetCoords & position = getField()->getPosition();
	banner = getStyle()->createBanner(position, id);
	token = getStyle()->createToken(position, TOKEN_ID, getOwner());
}

float Unit::getTotalStrength()
{
	return (float)this->health * (float)this->strength / 100;
}

Unit::Unit(int id, Field* field, Player& owner) : id(id), InGameObject(field, owner)
{
	init();
}

Unit::Unit(int id, Field* field, Player & owner, std::string const& name, int speed, int strength, UnitType type)
	: id(id), name(name), speed(speed), strength(strength), movement_points(speed), type(type), InGameObject(field, owner)
{
	init();
}

Unit::~Unit()
{
}

CombatResult Unit::attack(InGameObject * target)
{
	setIfAttackedThisTurn(true);
	float strength = getTotalStrength();
	int damaged;
	CombatResult result = target->attacked(strength, damaged);
	this->health -= damaged;
	if (this->health <= 0)
	{
		if (result == CombatResult::Win)
		{
			this->health = 1;
			return CombatResult::Win;
		}
		else
			return CombatResult::Lose;
	}
	return result;
}

CombatResult Unit::attacked(float strength, int & counter_damage)
{
	float strength_ratio = strength / getTotalStrength();
	float damage = pow(strength_ratio, 2) * 10 - strength_ratio * 10 + 30;
	float counter = damage / (pow(strength_ratio, 2) * 2 - strength_ratio * 4 + 3);
	
	if (strength_ratio >= 1)
	{
		this->health -= damage;
		counter_damage = counter;
	}
	else
	{
		this->health -= counter;
		counter_damage = damage;
	}

	if (this->health > 0)
		return CombatResult::Tie;
	else
		return CombatResult::Win;
}

void Unit::spendActionPoints(uint32_t points)
{
	if (points == max_movement_points)
		this->movement_points = 0;
	else
		this->movement_points -= points;
}

Occupied Unit::checkIfOccupied(Field * field)
{
	InGameObject * object = field->objects().top();
	if (object == nullptr)
		return Occupied::Empty;
	else 
	{
		if (object->getOwner() != this->getOwner())
			return Occupied::Enemy;
		else
		{
			Unit * unit = dynamic_cast<Unit*>(object);
			if (field->objects().containsUnitType(this->getType()))
				return Occupied::Full;
			else
				return Occupied::Empty;
		}
	}
}
