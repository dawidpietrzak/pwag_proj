#pragma once

#include <GL/glew.h>
#include <vector>

#include <Engine/Rendering/OpenGL/VertexBuffer.h>

namespace engine
{
	class VertexAttrib
	{
	public:
		VertexAttrib();
		~VertexAttrib();

		void Create(const std::vector<GLuint>& count);

		void Bind() const;
		void Unbind() const;

	private:
		GLuint m_id = 0;
		GLuint m_stride = 0;
		std::vector<GLuint> m_layout;
	};
}



