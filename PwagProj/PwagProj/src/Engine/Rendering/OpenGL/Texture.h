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

		void Bind() const;
		void Unbind() const;

		bool IsCreated() const { return m_id != 0; }

	private:
		GLuint m_id = 0;
		Image m_image;
	};
}

