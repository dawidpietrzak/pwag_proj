#pragma once

#include <vector>
#include <string>

namespace engine
{
	class FileTools
	{
	public:
		static std::vector<std::string> ReadAllLines(const std::string& fileName);
	};
}