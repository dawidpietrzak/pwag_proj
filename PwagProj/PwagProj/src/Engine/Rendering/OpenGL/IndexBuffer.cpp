#include "IndexBuffer.h"

namespace engine
{
	IndexBuffer::IndexBuffer()
	{
		
	}

	void IndexBuffer::Create(const std::vector<GLuint>& indices)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		m_indicesCount = (GLuint)indices.size();
	}

	void IndexBuffer::Destroy()
	{
		glDeleteBuffers(1, &m_id);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
