#include "ImageTools.h"

#include <STB/stb_image.h>

namespace engine
{
	void Image::Free()
	{
		if (ColorData)
			stbi_image_free(ColorData);
	}

	Image ImageTools::LoadImageFromFile(const std::string& filePath)
	{
		FILE* f = NULL;
		errno_t errors = fopen_s(&f, filePath.c_str(), "rb");
		if (errors > 0 || f == NULL)
			throw std::exception("Could not load image from a file");

		int width, height, bpp;
		uint8_t* data = stbi_load_from_file(f, &width, &height, &bpp, 4);
		if (!data)
			throw std::exception("Could not load image from a file");

		fclose(f);

		Image image;
		image.Width = (uint32_t)width;
		image.Height = (uint32_t)height;
		image.BytesPerPixel = (uint8_t)bpp;
		image.ColorData = data;
		return image;
	}
}