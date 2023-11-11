#pragma once

#include <GL/glew.h>
#include <vector>

#include <Engine/Rendering/OpenGL/VertexAttrib.h>

namespace engine
{
	class VertexBuffer
	{
	public:
		VertexBuffer();

		void Create(const std::vector<GLfloat>& vertices, const VertexAttrib& vertexAttrib);
		void Destroy();

		void Bind() const;
		void Unbind() const;

	private:
		GLuint m_id = 0;
		VertexAttrib m_attrib;
	};
}



