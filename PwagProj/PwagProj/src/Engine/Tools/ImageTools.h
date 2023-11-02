#pragma once

#include <cstdint>
#include <string>

namespace engine
{
	struct Image
	{
		uint32_t Width = 0;
		uint32_t Height = 0;
		uint8_t* ColorData = nullptr;
		uint8_t BytesPerPixel = 0;

		void Free();
	};

	class ImageTools
	{
	public:
		static Image LoadImageFromFile(const std::string& filePath);
	};
}



