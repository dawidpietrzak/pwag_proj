#pragma once

#include <Engine/Rendering/OpenGL/VertexBuffer.h>
#include <Engine/Rendering/OpenGL/VertexAttrib.h>
#include <Engine/Rendering/OpenGL/IndexBuffer.h>

namespace engine
{
	class Mesh
	{
	public:
		void Create(VertexBuffer vertexBuffer, VertexAttrib vertexAttrib, IndexBuffer indexBuffer);
		void Destroy();

		void Bind();
		void Unbind();

		GLuint GetIndicesCount() const { return m_indexBuffer.GetIndicesCount(); }

	private:
		VertexBuffer m_vertexBuffer;
		VertexAttrib m_vertexAttrib;
		IndexBuffer m_indexBuffer;
	};
}



