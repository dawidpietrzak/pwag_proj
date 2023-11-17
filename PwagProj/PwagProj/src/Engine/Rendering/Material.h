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

		void Bind() const;
		void Unbind() const;

		void SetProjectionMatrix(const glm::mat4& projectionMatrix);
		void SetViewMatrix(const glm::mat4& viewMatrix);
		void SetModelMatrix(const glm::mat4& modelMatrix);
		void SetLightProjectionMatrix(const glm::mat4& lightProjectionMatrix);
		void SetLightViewMatrix(const glm::mat4& lightViewMatrix);
		void SetLightPosition(const glm::vec3& lightPosition);
		void SetIsShadowPass(bool isShadowPass);

		void SetTexture(Texture texture) { m_texture = texture; }
		void SetDepthTexture(Texture texture) { m_depthTexture = texture; }

	private:
		Shader m_shader;
		Texture m_texture;
		Texture m_depthTexture;
	};
}