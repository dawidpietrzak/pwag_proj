#include "Mesh.h"

namespace engine
{
	void Mesh::Create(VertexBuffer vertexBuffer, VertexAttrib vertexAttrib, IndexBuffer indexBuffer)
	{
		m_vertexBuffer = vertexBuffer;
		m_vertexAttrib = vertexAttrib;
		m_indexBuffer = indexBuffer;
	}

	void Mesh::Bind()
	{
		m_vertexBuffer.Bind();
		m_vertexAttrib.Bind();
		m_indexBuffer.Bind();
	}

	void Mesh::Unbind()
	{
		m_vertexBuffer.Unbind();
		m_vertexAttrib.Unbind();
		m_indexBuffer.Unbind();
	}

	void Mesh::Destroy()
	{
		m_vertexBuffer.Destroy();
		m_indexBuffer.Destroy();
	}
}