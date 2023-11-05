#include "Entity.h"

#include <GLM/gtc/matrix_transform.hpp>

namespace engine
{
	void Entity::Create(const Mesh& mesh, const Material& material)
	{
		m_mesh = mesh;
		m_material = material;
	}

	void Entity::Bind() const
	{
		m_mesh.Bind();
		m_material.Bind();
	}

	void Entity::SetPosition(const glm::vec3& position)
	{
		m_position = position;
		RebuildTransformMatrix();
	}

	void Entity::Translate(const glm::vec3& translation)
	{
		m_position += translation;
		m_transform = glm::translate(m_transform, translation);
	}

	void Entity::SetRotation(const glm::vec3& rotation)
	{
		m_rotation = rotation;
		RebuildTransformMatrix();
	}

	void Entity::Rotate(const glm::vec3& rotation)
	{
		m_rotation += rotation;
		m_transform = glm::rotate(m_transform, m_rotation.z, glm::vec3(0, 0, 1));
		m_transform = glm::rotate(m_transform, m_rotation.y, glm::vec3(0, 1, 0));
		m_transform = glm::rotate(m_transform, m_rotation.x, glm::vec3(1, 0, 0));
	}

	void Entity::SetScale(const glm::vec3& scale)
	{
		m_scale = scale;
		RebuildTransformMatrix();
	}

	void Entity::Scale(const glm::vec3& scale)
	{
		m_scale += scale;
		m_transform = glm::scale(m_transform, scale);
	}

	void Entity::RebuildTransformMatrix()
	{
		m_transform = glm::mat4(1.0f);
		m_transform = glm::scale(m_transform, m_scale);
		m_transform = glm::rotate(m_transform, m_rotation.z, glm::vec3(0, 0, 1));
		m_transform = glm::rotate(m_transform, m_rotation.y, glm::vec3(0, 1, 0));
		m_transform = glm::rotate(m_transform, m_rotation.x, glm::vec3(1, 0, 0));
		m_transform = glm::translate(m_transform, m_position);
	}
}