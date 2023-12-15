#pragma once

#include <GL/glew.h>
#include <Engine/Tools/ImageTools.h>

#include <vector>

namespace engine
{
	enum class TextureType
	{
		None,
		Image2D,
		Depth,
		CubeMap
	};

	class Texture
	{
	public:
		void CreateFromImage(const Image& image);
		void CreateDepthTexture(uint32_t width, uint32_t height);
		void CreateCubeMap(const std::vector<Image>& images);
		void Destroy();

		void Bind() const;
		void Unbind() const;

		GLuint GetId() const { return m_id; }
		bool IsCreated() const { return m_id != 0; }

	private:
		GLuint m_id = 0;
		uint32_t m_width = 0;
		uint32_t m_height = 0;

		TextureType m_type = TextureType::None;
	};
}

