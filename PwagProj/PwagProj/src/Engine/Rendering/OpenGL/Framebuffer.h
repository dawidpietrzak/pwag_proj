#pragma once

#include <GL/glew.h>
#include <cstdint>

#include <Engine/Rendering/OpenGL/Texture.h>

namespace engine
{
	class Framebuffer
	{
	public:
		void CreateDepthBuffer(uint32_t width, uint32_t height);
		void Destroy();

		void Bind() const;
		void Unbind() const;

		Texture& GetTexture() { return m_texture; }

		uint32_t GetWidth() const { return m_width; }
		uint32_t GetHeight() const { return m_height; }

	private:
		GLuint m_id;
		Texture m_texture;

		uint32_t m_width;
		uint32_t m_height;
	};
}