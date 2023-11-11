#pragma once

#include <Engine/Rendering/OpenGL/VertexBuffer.h>
#include <Engine/Rendering/OpenGL/VertexAttrib.h>
#include <Engine/Rendering/OpenGL/IndexBuffer.h>

namespace engine
{
	class Mesh
	{
	public:
		void Create(VertexBuffer vertexBuffer, IndexBuffer indexBuffer);
		void Create(const std::vector<VertexBuffer>& vertexBuffers, IndexBuffer indexBuffer);
		void CreateInstanced(const std::vector<VertexBuffer>& vertexBuffers, IndexBuffer indexBuffer, GLuint instancesNumber);
		void Destroy();

		void Bind() const;
		void Unbind() const;

		GLuint GetIndicesCount() const { return m_indexBuffer.GetIndicesCount(); }
		GLuint GetInstanceCount() const { return m_instanceCount; }

		bool IsCreated() const { return !m_vertexBuffers.empty(); }

	private:
		std::vector<VertexBuffer> m_vertexBuffers;
		IndexBuffer m_indexBuffer;
		GLuint m_instanceCount = 1;
	};
}



