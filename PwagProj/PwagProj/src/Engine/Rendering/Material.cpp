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
}