#include "Material.h"

namespace engine
{
	void Material::Bind() const
	{
		m_shader.Bind();
		if (m_texture.IsCreated())
		{
			m_shader.SetInt("uTexture", 0);
			glActiveTexture(GL_TEXTURE0);
			m_texture.Bind();
		}
		if (m_depthTexture.IsCreated())
		{
			m_shader.SetInt("uDepthTexture", 1);
			glActiveTexture(GL_TEXTURE0 + 1);
			m_depthTexture.Bind();
		}
	}

	void Material::Unbind() const
	{
		m_shader.Unbind();
	}

	void Material::SetProjectionMatrix(const glm::mat4& projectionMatrix)
	{
		m_shader.SetMat4f("uProjectionMatrix", projectionMatrix);
	}

	void Material::SetViewMatrix(const glm::mat4& viewMatrix)
	{
		m_shader.SetMat4f("uViewMatrix", viewMatrix);
	}

	void Material::SetModelMatrix(const glm::mat4& modelMatrix)
	{
		m_shader.SetMat4f("uModelMatrix", modelMatrix);
	}

	void Material::SetLightProjectionMatrix(const glm::mat4& lightProjectionMatrix)
	{
		m_shader.SetMat4f("uLightProjectionMatrix", lightProjectionMatrix);
	}

	void Material::SetLightViewMatrix(const glm::mat4& lightViewMatrix)
	{
		m_shader.SetMat4f("uLightViewMatrix", lightViewMatrix);
	}

	void Material::SetLightPosition(const glm::vec3& lightPosition)
	{
		m_shader.SetVec3f("uLightPos", lightPosition);
	}

	void Material::SetIsShadowPass(bool isShadowPass)
	{
		m_shader.SetInt("uShadowPass", (int)isShadowPass);
	}
}