#include "Renderer.h"

namespace engine
{
	std::shared_ptr<Camera> Renderer::s_camera;

	void Renderer::Begin(const std::shared_ptr<Camera>& camera)
	{
		s_camera = camera;
	}

	void Renderer::Draw(const Entity& entity)
	{
		entity.Bind();

		Material material = entity.GetMaterial();
		material.SetProjectionMatrix(s_camera->GetProjectionMatrix());
		material.SetViewMatrix(s_camera->GetViewMatrix());
		material.SetModelMatrix(entity.GetTransformMatrix());

		Mesh mesh = entity.GetMesh();
		GLuint instanceCount = mesh.GetInstanceCount();
		if (instanceCount > 1)
		{
			glDrawElementsInstanced(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, 0, (GLsizei)instanceCount);
		}
		else
		{
			glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, 0);
		}
	}

	void Renderer::Draw(const std::unique_ptr<Entity>& entity)
	{
		Draw(*entity);
	}

	void Renderer::Draw(const std::shared_ptr<Entity>& entity)
	{
		Draw(*entity);
	}

	void Renderer::End()
	{

	}
}