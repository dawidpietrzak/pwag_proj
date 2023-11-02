#include "FileTools.h"

#include <fstream>

namespace engine
{
	std::vector<std::string> FileTools::ReadAllLines(const std::string& fileName)
	{
		std::ifstream inputFile(fileName, std::ios::in);
		if (!inputFile.is_open())
		{
			return {};
		}

		std::vector<std::string> lines;
		std::string line;
		while (std::getline(inputFile, line))
		{
			lines.push_back(line);
		}
		
		inputFile.close();
		return lines;
	}
}