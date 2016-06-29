#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include "Fields.h"
#include <vector>
#include "Deposits.h"
#include "GameExceptions.h"
#include "EngineDefinitions.h"

class GameMap;

class MapFileReader
{
private:
	GameMap * target;
	std::vector<Player> & players;
	sf::Vector2u size;

	void readSize(std::string & str);

	template <typename TDeposit>
	inline void addDeposit(Field * field);

public:
	void load(std::string & file_path);

	MapFileReader(GameMap * target, std::vector<Player> & players);
	~MapFileReader();
};

#include "GameMap.h"

template<typename TDeposit>
inline void MapFileReader::addDeposit(Field * field)
{
	if (field->getDeposit() == nullptr)
		field->newDeposit<TDeposit>();
}
