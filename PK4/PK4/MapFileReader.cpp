#include "MapFileReader.h"

namespace
{
	const size_t TOKEN_LENGTH = 4;

	const char FIELD_DESERT = 'D';
	const char FIELD_FOREST = 'F';
	const char FIELD_GRASS = 'G';
	const char FIELD_HILLS = 'H';
	const char FIELD_MOUNTAINS = 'M';
	const char FIELD_WATER = 'W';

	const char DEP_GEMS = 'g';
	const char DEP_IRON = 'i';
	const char DEP_PEARLS = 'p';

	const char UNIT_ARCHER = 'A';
	const char UNIT_DRAGON = 'D';
	const char UNIT_HORSEMAN = 'H';
	const char UNIT_SHIP = 'N';
	const char UNIT_SWORDSMAN = 'S';
	const char UNIT_WORKER = 'W';

	const char NO_ARG = '_';
}

void MapFileReader::readSize(std::string & str)
{
	std::stringstream ss(str);
	std::string token;
	std::string::size_type result;

	ss >> token;
	this->size.x = std::stoi(token, &result);
	if (result != token.length())
		throw MapLoadException(std::string("Invalid map width"));
	ss >> token;
	this->size.y = std::stoi(token, &result);
	if (result != token.length())
		throw MapLoadException(std::string("Invalid map height"));
	
}

void MapFileReader::load(std::string & file_path)
{
	std::ifstream file;
	file.open(file_path);
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		std::getline(file, line);
		std::getline(file, line);
		readSize(line);
		this->target->resetMap(this->size);

		OffsetCoords actual(0, 0);

		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			std::string token;

			actual.x = 0;
			while (ss >> token)
			{
				if (token.length() != TOKEN_LENGTH)
					throw MapLoadException("MapLoadException: Invalid token length (" + std::to_string(token.length()) + ") must be (" + std::to_string(TOKEN_LENGTH) + ")");
				Field * field;

				switch (token[0])
				{
				case FIELD_DESERT:
					field = target->newField<Desert>(actual);
					break;
				case FIELD_FOREST:
					field = target->newField<Forest>(actual);
					break;
				case FIELD_GRASS:
					field = target->newField<Grass>(actual);
					break;
				case FIELD_HILLS:
					field = target->newField<Hills>(actual);
					break;
				case FIELD_MOUNTAINS:
					field = target->newField<Mountains>(actual);
					break;
				case FIELD_WATER:
					field = target->newField<Water>(actual);
					break;
				default:
				case NO_ARG:
					throw MapLoadException(std::string("MapLoadException: Null not allowed at field type"));
				}

				switch (token[1])
				{
				case DEP_GEMS:
					addDeposit<GemsDeposit>(field);
					break;
				case DEP_IRON:
					addDeposit<IronDeposit>(field);
					break;
				case DEP_PEARLS:
					addDeposit<PearlsDeposit>(field);
					break;
				case NO_ARG:
					break;
				default:
					throw MapLoadException(std::string("MapLoadException: Unknown deposit symbol: ") + token[1]);
				}

				Player * player = nullptr;

				switch (token[2])
				{
				case NO_ARG:
					break;
				default:
				{
					int num = (int)token[2] - 48;
					if (num > 0 && num <= this->players.size())
						player = &this->players[num - 1];
					else
						throw MapLoadException(std::string("MapLoadException: Unknown player symbol: ") + token[2]);
				}
				}

				if (player != nullptr)
				{
					switch (token[3])
					{
					case UNIT_ARCHER:
						field->newUnit<Archer>(*player);
						break;
					case UNIT_DRAGON:
						field->newUnit<Dragon>(*player);
						break;
					case UNIT_HORSEMAN:
						field->newUnit<Horseman>(*player);
						break;
					case UNIT_SHIP:
						field->newUnit<Ship>(*player);
						break;
					case UNIT_SWORDSMAN:
						field->newUnit<Swordsman>(*player);
						break;
					case UNIT_WORKER:
						field->newUnit<Worker>(*player);
						break;
					case NO_ARG:
					default:
						break;
					}
				}
				
				actual.x++;
			}
			actual.y++;
		}
	}
	else
		throw FileLoadException(file_path);
}


MapFileReader::MapFileReader(GameMap * target, std::vector<Player> & players) : target(target), players(players)
{
}

MapFileReader::~MapFileReader()
{
}
