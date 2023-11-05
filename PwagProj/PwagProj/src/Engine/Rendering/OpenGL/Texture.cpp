#include "Texture.h"



namespace engine
{
	void Texture::Create(const Image& image)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA, image.Width, image.Height,
			0, GL_RGBA, GL_UNSIGNED_BYTE, image.ColorData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		m_image = image;
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