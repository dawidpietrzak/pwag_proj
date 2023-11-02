#pragma once

#include <GL/glew.h>
#include <Engine/Tools/ImageTools.h>

namespace engine
{
	class Texture
	{
	public:
		void Create(const Image& image);
		void Destroy();

		void Bind();
		void Unbind();

		bool IsCreated() const { return m_id != 0; }

	private:
		GLuint m_id = 0;
		Image m_image;
	};
}

