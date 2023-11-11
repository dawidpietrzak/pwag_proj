#include "VertexBuffer.h"

namespace engine
{
	VertexBuffer::VertexBuffer()
	{
		
	}

	void VertexBuffer::Create(const std::vector<GLfloat>& vertices, const VertexAttrib& vertexAttrib)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_attrib = vertexAttrib;
	}

	void VertexBuffer::Destroy()
	{
		glDeleteBuffers(1, &m_id);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		m_attrib.Bind();
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_attrib.Unbind();
	}
}
