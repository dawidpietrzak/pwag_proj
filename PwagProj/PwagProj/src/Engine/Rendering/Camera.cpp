#include "Camera.h"

#include <GLM/gtc/matrix_transform.hpp>

namespace engine
{
	Camera::Camera()
	{
		m_projectionMatrix = glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
		m_viewMatrix = glm::lookAt(
			glm::vec3(0.0f, 5.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		m_position = { 0, 5.0f, 0.0f };
		m_rotation = { 0, 0, 0 };

		m_forward = { 0, 0, -1 };
		m_right = { 1, 0, 0 };
		m_up = { 0, 1, 0 };
	}

	void Camera::MoveForward(float move)
	{
		m_position += m_forward * move;
		m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, glm::vec3(0, 1, 0));
	}

	void Camera::MoveBackward(float move)
	{
		m_position += -m_forward * move;
		m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, glm::vec3(0, 1, 0));
	}

	void Camera::MoveLeft(float move)
	{
		m_position += -m_right * move;
		m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, glm::vec3(0, 1, 0));
	}

	void Camera::MoveRight(float move)
	{
		m_position += m_right * move;
		m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, glm::vec3(0, 1, 0));
	}

	void Camera::MoveUp(float move)
	{
		m_position += m_up * move;
		m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, glm::vec3(0, 1, 0));
	}

	void Camera::MoveDown(float move)
	{
		m_position += -m_up * move;
		m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, glm::vec3(0, 1, 0));
	}

	void Camera::Translate(const glm::vec3& translation)
	{
		m_position += translation;
		m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, glm::vec3(0, 1, 0));
	}

	void Camera::Rotate(const glm::vec3& rotation)
	{
		m_rotation += rotation;

		RecalulateOrientationVectors();
		m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, glm::vec3(0, 1, 0));
	}

	void Camera::RecalulateOrientationVectors()
	{
		glm::vec3 forward = { 0, 0, 0 };
		forward.x = cos(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));
		forward.y = -sin(glm::radians(m_rotation.y));
		forward.z = sin(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));

		m_forward = glm::normalize(forward);
		m_right = glm::normalize(glm::cross(m_forward, { 0, 1, 0 }));
		m_up = glm::normalize(glm::cross(m_right, m_forward));
	}
}
