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

		void Bind() const;
		void Unbind() const;

		void SetInt(const std::string& uniformName, int value) const;
		void SetVec3f(const std::string& uniformName, const glm::vec3& vector) const;
		void SetMat4f(const std::string& uniformName, const glm::mat4& matrix) const;

	private:
		GLuint m_id;
	};
}