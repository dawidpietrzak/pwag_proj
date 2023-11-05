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

		void Bind() const;
		void Unbind() const;

	private:
		GLuint m_id = 0;
	};
}



