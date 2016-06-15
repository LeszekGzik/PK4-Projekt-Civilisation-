#include "Unit.h"

ObjectStyle * Unit::object_style = NULL;


void Unit::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(token);
	target.draw(flag);
}

void Unit::move(AxialCoords coords)
{
	PixelCoords pixels = object_style->hex().toPixel(coords);
	pixels.x += object_style->hex().horizontalSize() / 2;
	pixels.y += object_style->hex().verticalSize() / 2;
	move(pixels);
}

void Unit::move(PixelCoords coords)
{
	object_style->move(coords, getPosition(), token);
	object_style->move(coords, getPosition(), flag);
	setPosition(object_style->hex().toAxial(coords));
}

void Unit::newTurn()
{
	movement_points = speed;
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
	vector->push_back(ContextInfoLine(getOwner().getName(), ColorUtils::sfColor(getOwner().getColor())));
	vector->push_back(ContextInfoLine("HP: " + std::to_string(health), sf::Color::Black));
	vector->push_back(ContextInfoLine("STR: " + std::to_string(strength), sf::Color::Black));
	vector->push_back(ContextInfoLine("MOVE: " + std::to_string(movement_points) + "/" + std::to_string(speed), sf::Color(sf::Color::Black)));
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
	token = object_style->createToken(getPosition(), id, getOwner());
}

Unit::Unit(int id, AxialCoords position, Player& owner) : id(id), InGameObject(position, owner)
{
	init();
}

Unit::Unit(int id, AxialCoords position, Player & owner, std::string const& name, int speed, int strength) 
	: id(id), name(name), speed(speed), strength(strength), movement_points(speed), InGameObject(position, owner)
{
	init();
}

Unit::~Unit()
{
}

CombatResult Unit::attack(InGameObject * target)
{
	float strength = (float)getStrength() * (float)getHealth() / 100;
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
	float strength_ratio = strength / ((float)this->strength * (float)this->health / 100);
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

Occupied Unit::checkIfOccupied(Field * field)
{
	InGameObject * object = field->objects().top();
	if (object == nullptr)
		return Occupied::Empty;
	else if (object->getOwner() != this->getOwner())
		return Occupied::Enemy;
}
