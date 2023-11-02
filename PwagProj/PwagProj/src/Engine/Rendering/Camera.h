#pragma once

#include <GLM/glm.hpp>

namespace engine
{
	class Camera
	{
	public:
		Camera();

		const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }

	private:
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;
	};
}



