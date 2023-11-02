#pragma once

#include <GL/glew.h>
#include <vector>

namespace engine
{
	class IndexBuffer
	{
	public:
		IndexBuffer();

		void Create(const std::vector<GLuint>& indices);
		void Destroy();

		void Bind();
		void Unbind();

		GLuint GetIndicesCount() const { return m_indicesCount; }

	private:
		GLuint m_id = 0;
		GLuint m_indicesCount = 0;
	};
}



