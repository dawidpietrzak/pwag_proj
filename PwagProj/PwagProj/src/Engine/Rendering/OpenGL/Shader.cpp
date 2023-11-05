#include "Shader.h"

namespace engine
{
	void Shader::Bind() const
	{
		glUseProgram(m_id);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetInt(const std::string& uniformName, int value) const
	{
		GLuint uniformLocation = glGetUniformLocation(m_id, uniformName.c_str());
		glUniform1i(uniformLocation, value);
	}

	void Shader::SetMat4f(const std::string& uniformName, const glm::mat4& matrix) const
	{
		GLuint uniformLocation = glGetUniformLocation(m_id, uniformName.c_str());
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix[0][0]);
	}
}