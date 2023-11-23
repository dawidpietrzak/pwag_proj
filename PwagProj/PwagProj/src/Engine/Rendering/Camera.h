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

		void MoveForward(float move);
		void MoveBackward(float move);
		void MoveLeft(float move);
		void MoveRight(float move);
		void MoveUp(float move);
		void MoveDown(float move);

		void Translate(const glm::vec3& translation);

		void Rotate(const glm::vec3& rotation);

		glm::vec3 GetForward() const { return m_forward; }
		glm::vec3 GetUp() const { return m_up; }
		glm::vec3 GetRight() const { return m_right; }

	private:
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;

		glm::vec3 m_position;
		glm::vec3 m_rotation;

		glm::vec3 m_forward;
		glm::vec3 m_up;
		glm::vec3 m_right;

	private:
		void RecalulateOrientationVectors();
	};
}



