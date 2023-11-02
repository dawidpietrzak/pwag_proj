#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>

#include <string>
#include <unordered_map>

namespace engine
{
	class Shader
	{
	public:
		Shader() { m_id = 0; }
		Shader(GLuint programId) { m_id = programId; }

		void Destroy() { glDeleteProgram(m_id); m_id = 0; }

		void Bind();
		void Unbind();

		void SetInt(const std::string& uniformName, int value);
		void SetMat4f(const std::string& uniformName, const glm::mat4& matrix);

	private:
		GLuint m_id;
	};
}