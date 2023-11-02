#pragma once

#include <vector>
#include <string>

namespace engine
{
	class StringTools
	{
	public:
		static std::vector<std::string> Split(const std::string& toSplit, char by);
	};
}