#include "MapPackLoader.h"



MapPackLoader::MapPackLoader()
{
}


MapPackLoader::~MapPackLoader()
{
}

MapPackLoader::FileList MapPackLoader::getFiles(int player_number)
{
	FileList files;
	WIN32_FIND_DATA file;
	HANDLE search_handle = FindFirstFile("*.txt", &file);

	if (search_handle != nullptr)
	{
		do
		{
			MapFile map;
			bool result = false;
			try
			{
				map = checkFile(file, player_number, result);
			}
			catch (const std::exception&)
			{
				result = false;
			}
			if (result)
				files.push_back(map);
		} while (FindNextFile(search_handle, &file));
		if (!IsDebuggerPresent())
			CloseHandle(search_handle);
	}

	return files;
}

MapPackLoader::MapFile MapPackLoader::checkFile(WIN32_FIND_DATA file, int players, bool & result)
{
	MapFile map;
	map.path = file.cFileName;
	std::ifstream stream;
	stream.open(file.cFileName);

	if (stream.is_open())
	{
		std::string line;
		std::string::size_type size;

		if (std::getline(stream, line))
		{
			int number = std::stoi(line, &size);
			if (size != line.length() || number != players)
			{
				stream.close();
				result = false;
				return map;
			}
		}
		else
		{
			stream.close();
			result = false;
			return map;
		}

		if (std::getline(stream, line))
		{
			map.name = line;
		}
		else
		{
			stream.close();
			result = false;
			return map;
		}

		if (std::getline(stream, line))
		{
			std::stringstream ss(line);
			std::string token;

			ss >> token;
			map.size.x = std::stoi(line, &size);
			if (size != token.length())
			{
				stream.close();
				result = false;
				return map;
			}
			
			ss >> token;
			map.size.y = std::stoi(line, &size);
			if (size != token.length())
			{
				stream.close();
				result = false;
				return map;
			}
		}
		else
		{
			stream.close();
			result = false;
			return map;
		}

		stream.close();
		result = true;
		return map;
	}
	else
	{
		stream.close();
		result = false;
		return map;
	}
}
