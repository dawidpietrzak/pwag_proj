#include "Mesh.h"

namespace engine
{
	void Mesh::Create(VertexBuffer vertexBuffer)
	{
		m_vertexBuffers = { vertexBuffer };
		m_indexBuffer = {};
	}

	void Mesh::Create(VertexBuffer vertexBuffer, IndexBuffer indexBuffer)
	{
		m_vertexBuffers = { vertexBuffer };
		m_indexBuffer = indexBuffer;
	}

	void Mesh::Create(const std::vector<VertexBuffer>& vertexBuffers, IndexBuffer indexBuffer)
	{
		m_vertexBuffers = vertexBuffers;
		m_indexBuffer = indexBuffer;
	}

	void Mesh::CreateInstanced(const std::vector<VertexBuffer>& vertexBuffers, IndexBuffer indexBuffer, GLuint instancesNumber)
	{
		m_instanceCount = instancesNumber;
		Create(vertexBuffers, indexBuffer);
	}

	void Mesh::Bind() const
	{
		for (const auto& vertexBuffer : m_vertexBuffers)
			vertexBuffer.Bind();

		if (m_indexBuffer.GetIndicesCount() > 0)
			m_indexBuffer.Bind();
	}

	void Mesh::Unbind() const
	{
		for (const auto& vertexBuffer : m_vertexBuffers)
			vertexBuffer.Unbind();
		m_indexBuffer.Unbind();
	}

	void Mesh::Destroy()
	{
		for (auto& vertexBuffer : m_vertexBuffers)
			vertexBuffer.Destroy();
		
		if (m_indexBuffer.GetIndicesCount() > 0)
			m_indexBuffer.Destroy();
	}
}