#pragma once

#include <GL/glew.h>
#include <vector>

namespace engine
{
	class VertexBuffer
	{
	public:
		VertexBuffer();

		void Create(const std::vector<GLfloat>& vertices);
		void Destroy();

		void Bind();
		void Unbind();

	private:
		GLuint m_id = 0;
	};
}



