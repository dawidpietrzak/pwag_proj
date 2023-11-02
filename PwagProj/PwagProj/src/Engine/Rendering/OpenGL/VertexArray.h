#pragma once

#include <GL/glew.h>
#include <vector>

#include <Engine/Rendering/OpenGL/VertexBuffer.h>
#include <Engine/Rendering/OpenGL/IndexBuffer.h>

namespace engine
{
	class VertexArray
	{
	public:
		VertexArray();

		void Create(VertexBuffer vertexBuffer, IndexBuffer indexBuffer);
		void Destroy();

		void Bind();
		void Unbind();

	private:
		GLuint m_id = 0;
	};
}



