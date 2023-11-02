#include "VertexArray.h"

namespace engine
{
	VertexArray::VertexArray()
	{
		
	}

	void VertexArray::Create(VertexBuffer vertexBuffer, IndexBuffer indexBuffer)
	{
		glGenVertexArrays(1, &m_id);
		glBindVertexArray(m_id);
		vertexBuffer.Bind();
		indexBuffer.Bind();
	}

	void VertexArray::Destroy()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}
}