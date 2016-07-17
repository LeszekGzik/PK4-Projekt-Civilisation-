#include "GameMap.h"
#include <functional>
#include <algorithm>


void GameMap::drawGrid(sf::RenderTarget & window, sf::RenderStates states, sf::IntRect visibility) const
{
	for (int i = visibility.left; i < visibility.width; i++)
	{
		for (int j = visibility.top; j < visibility.height; j++)
		{
			sf::VertexArray hex = hex_style.create(OffsetCoords(i, j));
			window.draw(hex);
		}
	}
}

void GameMap::drawMap(sf::RenderTarget & window, sf::RenderStates states, sf::IntRect visibility) const
{
	for (int j = visibility.top; j < visibility.height; j++)
	{
		for (int i = visibility.left; i < visibility.width; i++)
		{
			getField(OffsetCoords(i, j))->draw(window, states);
		}
	}
}

void GameMap::loadFromFile(std::string & file_path, std::vector<Player> & players)
{
	MapFileReader reader(this, players);
	reader.load(file_path);
}

sf::IntRect GameMap::visibilityCheck(sf::View view) const
{
	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();
	sf::IntRect visibility_px;
	sf::IntRect visibility_hex;

	visibility_px.left = floorf((center.x - size.x / 2) / hex_style.horizontalSize() - 1);
	visibility_px.top = floorf(2 * (center.y - size.y / 2) / (hex_style.verticalSize() + hex_style.edgeSize()));
	visibility_px.width = ceilf((center.x + size.x / 2) / hex_style.horizontalSize());
	visibility_px.height = ceilf(2 * (center.y + size.y / 2) / (hex_style.verticalSize() + hex_style.edgeSize()));

	if (visibility_px.left < 0)
		visibility_hex.left = 0;
	else
		visibility_hex.left = visibility_px.left;

	if (visibility_px.top < 0)
		visibility_hex.top = 0;
	else
		visibility_hex.top = visibility_px.top;

	if (visibility_px.width > grid_size.x)
		visibility_hex.width = grid_size.x;
	else
		visibility_hex.width = visibility_px.width;

	if (visibility_px.height > grid_size.y)
		visibility_hex.height = grid_size.y;
	else
		visibility_hex.height = visibility_px.height;

	
	return visibility_hex;
}

Field * GameMap::getField(OffsetCoords pos) const
{
	if (OffsetCoords(grid_size.x, grid_size.y) > pos && pos > OffsetCoords(-1,-1))
		return board[pos.x][pos.y];
	else
		return nullptr;
}


Field * GameMap::getField(PixelCoords pos) const
{
	return getField(hex_style.toAxial(pos));
}

Field * GameMap::neighbour(OffsetCoords position, int32_t direction) const
{
	return getField(Neighbours::get(position, direction));
}

void GameMap::setField(OffsetCoords pos, Field * field)
{
	this->board[pos.x][pos.y] = field;
}

int GameMap::getDistance(const AxialCoords& from, const AxialCoords& to) const
{
	return (abs(from.x - to.x) + abs(from.x + from.y - to.x - to.y)
		+ abs(from.y - to.y)) / 2;
}

sf::Vector2f GameMap::getSizeInPixel()
{
	return sf::Vector2f(grid_size.x * hex_style.verticalSize(), grid_size.y * hex_style.horizontalSize());
}

void GameMap::moveUnit(OffsetCoords start, OffsetCoords goal)
{
	InGameObject * obj = getField(start)->objects().top();
	Field * target_field = getField(goal);
	Unit * unit = dynamic_cast<Unit*>(obj);
	bool success = false;
	
	if (unit == nullptr || unit->getActionPoints() == 0 || start == goal || unit->checkMovement(getField(goal)) < 0
		|| (target_field->objects().top() != nullptr && target_field->objects().top()->getOwner() != unit->getOwner() && !unit->canAttack()))
		return;

	auto frontier_compare = [](const NodePriorityPair& left, const NodePriorityPair& right) { return (left.second > right.second); };
	auto cost_compare = [](const OffsetCoords& left, const OffsetCoords& right) { return (left == right); };
	auto cost_hash = [](const OffsetCoords& key) -> size_t { return std::hash<int>()(key.x) ^ std::hash<int>()(key.y) << 1; };
	std::priority_queue<NodePriorityPair, std::vector<NodePriorityPair>, decltype(frontier_compare)> frontier(frontier_compare);
	std::unordered_map<OffsetCoords, OffsetCoords, decltype(cost_hash), decltype(cost_compare)> came_from(pathfinding_hash_bucket, cost_hash, cost_compare);
	std::unordered_map<OffsetCoords, int, decltype(cost_hash), decltype(cost_compare)> cost_so_far(pathfinding_hash_bucket, cost_hash, cost_compare);

	frontier.push(std::make_pair(start, 0));
	cost_so_far[start] = 0;

	int step = 0;

	while (!frontier.empty() && step < pathfinding_max_iterations)
	{
		OffsetCoords current = frontier.top().first;

		if (goal == current)
		{
			success = true;
			break;
		}

		frontier.pop();

		Field * current_field = getField(current);

		for (int i = 0; i < HEX_NEIGHBOURS; i++)
		{
			OffsetCoords next = Neighbours::get(current, i);
			Field * next_field = getField(next);
			if (next_field == nullptr)
				continue;
			int new_cost = cost_so_far[current] + unit->checkMovement(current_field);
			if (unit->checkMovement(next_field) >= 0 && !(unit->checkIfOccupied(next_field) == Occupied::Enemy && next != goal) && (cost_so_far.count(next) == 0 || new_cost < cost_so_far[next]))
			{
				cost_so_far[next] = new_cost;
				frontier.emplace(std::make_pair(next, new_cost + getDistance(goal, next)));
				came_from[next] = current;
			}
		}

		step++;
	}

	if (success)
	{
		OffsetCoords current = goal;
		std::list<Field*> path;
		path.push_back(getField(current));
		int c = came_from.count(goal);
		while (current != start)
		{
			current = came_from[current];
			path.push_back(getField(current));
		}

		std::list<Field*>::reverse_iterator target;
		int movement = unit->getActionPoints();

		std::list<Field*>::reverse_iterator it = path.rbegin();
		it++;
		for (it; it != path.rend(); it++)
		{
			movement -= unit->checkMovement(*it);
			target = it;
			if (movement <= 0)
			{
				movement = 0;
				break;
			}
		}

		unit->setActionPoints(movement);
		getField(start)->objects().pop();


		if (unit->checkIfOccupied(*target) == Occupied::Enemy)
		{
			std::list<Field*>::reverse_iterator previous = target;
			previous--;
			unit->move(*previous);
			ManagmentStatus status = unit->initCombat(*target);
			switch (status)
			{
			default:
			case ManagmentStatus::NoAction:
				break;
			case ManagmentStatus::Delete:
				delete unit;
				break;
			case ManagmentStatus::Null:
				(*previous)->objects().pop();
				break;
			}
		}
		else
		{
			unit->move(*target);
		}
	}
}

void GameMap::newTurn()
{
	for (int i = 0; i < grid_size.x; i++)
	{
		for (int j = 0; j < grid_size.y; j++)
		{
			board[i][j]->newTurn();
		}
	}
}

void GameMap::resetMap(sf::Vector2u new_size)
{
	if (board != nullptr)
	{
		for (int i = 0; i < grid_size.x; i++)
		{
			for (int j = 0; j < grid_size.y; j++)
				delete board[i][j];
			delete[grid_size.y] board[i];
		}
		delete[grid_size.x] board;
	}

	this->grid_size = new_size;

	board = new Field**[grid_size.x];
	for (int i = 0; i < grid_size.x; i++)
	{
		board[i] = new Field*[grid_size.y];
	}
}

void GameMap::draw(sf::RenderTarget & window, sf::RenderStates states) const
{
	sf::IntRect visibility = visibilityCheck(window.getView());
	drawMap(window, states, visibility);
	if (show_grid)
		drawGrid(window, states, visibility);
}


GameMap::GameMap(Hex& style) : hex_style(style), show_grid(false)
{
	tex_hex_style = TexturedHex(style);
	Field::setStyle(&tex_hex_style);
	Deposit::setStyle(&tex_hex_style);
	Unit::setStyle(&tex_hex_style);
}

GameMap::~GameMap()
{
	for (int i = 0; i < grid_size.x; i++)
	{
		delete[grid_size.y] board[i];
	}
	delete board;
}
