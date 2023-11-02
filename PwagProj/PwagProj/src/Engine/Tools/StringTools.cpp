#include "StringTools.h"

#include <sstream>

namespace engine
{
	std::vector<std::string> StringTools::Split(const std::string& toSplit, char by)
	{
		std::vector<std::string> results;
		std::stringstream current;

		size_t currentSize = 0;
		for (const char c : toSplit)
		{
			if (c == by)
			{
				results.push_back(current.str());
				current.str("");
				currentSize = 0;
			}
			else
			{
				current << c;
				currentSize++;
			}
		}

		if (currentSize > 0)
			results.push_back(current.str());

		return results;
	}
}