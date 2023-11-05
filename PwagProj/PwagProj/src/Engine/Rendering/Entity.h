#pragma once

#include <GLM/glm.hpp>
#include <Engine/Rendering/Mesh.h>
#include <Engine/Rendering/Material.h>

namespace engine
{
	class Entity
	{
	public:
		Entity() { }

		Entity(const Mesh& mesh, const Material& material)
			: m_mesh(mesh), m_material(material) { }

		void Create(const Mesh& mesh, const Material& material);
		void Bind() const;

		Mesh GetMesh() const { return m_mesh; }
		Material GetMaterial() const { return m_material; }

		void SetMesh(const Mesh& mesh) { m_mesh = mesh; }
		void DestroyMesh() { m_mesh.Destroy(); }

		void SetPosition(const glm::vec3& position);
		void Translate(const glm::vec3& translation);

		void SetRotation(const glm::vec3& rotation);
		void Rotate(const glm::vec3& rotation);

		void SetScale(const glm::vec3& scale);
		void Scale(const glm::vec3& scale);

		const glm::mat4& GetTransformMatrix() const { return m_transform; }

	private:
		Mesh m_mesh;
		Material m_material;
		glm::mat4 m_transform = glm::mat4(1.0f);
		glm::vec3 m_position = {};
		glm::vec3 m_rotation = {};
		glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	private:
		void RebuildTransformMatrix();
	};
}



