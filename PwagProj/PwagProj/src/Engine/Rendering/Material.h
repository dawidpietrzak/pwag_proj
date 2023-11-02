#pragma once

#include <Engine/Rendering/OpenGL/Texture.h>
#include <Engine/Rendering/OpenGL/Shader.h>
#include <GLM/glm.hpp>

namespace engine
{
	class Material
	{
	public:
		Material() { }
		Material(Shader shader) : m_shader(shader) { }

		void Bind();
		void Unbind();

		void SetProjectionMatrix(const glm::mat4& projectionMatrix);
		void SetViewMatrix(const glm::mat4& viewMatrix);

		void SetTexture(Texture texture) { m_texture = texture; }

	private:
		Shader m_shader;
		Texture m_texture;
	};
}