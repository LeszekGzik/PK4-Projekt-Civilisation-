#include "EngineDefinitions.h"

const float ENGINE::basic_unit = 120;
const float ENGINE::flag_size_factor = 0.5;
const float ENGINE::scroll_speed = 3.f;
const float ENGINE::scroll_distance = 30.f;

const sf::Vector2i Neighbours::neighbours[2][6] =
{ { sf::Vector2i(1, 0), sf::Vector2i(0, -1), sf::Vector2i(-1, -1), sf::Vector2i(-1, 0), sf::Vector2i(-1, 1), sf::Vector2i(0, 1) },
{ sf::Vector2i(1, 0), sf::Vector2i(1, -1), sf::Vector2i(0, -1), sf::Vector2i(-1, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 1) } };

OffsetCoords Neighbours::get(OffsetCoords field, int32_t n)
{
	int col = field.y & 1;
	return OffsetCoords(field.x + neighbours[col][n].x, field.y + neighbours[col][n].y);
}
