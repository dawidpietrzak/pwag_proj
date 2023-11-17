#include "Texture.h"



namespace engine
{
	void Texture::CreateFromImage(const Image& image)
	{
		m_width = image.Width;
		m_height = image.Height;

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA, image.Width, image.Height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, image.ColorData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	void Texture::CreateDepthTexture(uint32_t width, uint32_t height)
	{
		m_width = width;
		m_height = height;

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	void Texture::Destroy()
	{
		glDeleteTextures(1, &m_id);
		m_id = 0;
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}