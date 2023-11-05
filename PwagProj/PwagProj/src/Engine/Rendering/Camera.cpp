#include "Camera.h"

#include <GLM/gtc/matrix_transform.hpp>

namespace engine
{
	Camera::Camera()
	{
		m_projectionMatrix = glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
		m_viewMatrix = glm::lookAt(
			glm::vec3(0.0f, 12.0f, 12.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
	}
}
