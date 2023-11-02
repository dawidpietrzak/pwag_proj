#include "Renderer.h"

namespace engine
{
	std::shared_ptr<Camera> Renderer::s_camera;

	void Renderer::Begin(const std::shared_ptr<Camera>& camera)
	{
		s_camera = camera;
	}

	void Renderer::Draw(Mesh mesh, Material material)
	{
		mesh.Bind();

		material.Bind();
		material.SetProjectionMatrix(s_camera->GetProjectionMatrix());
		material.SetViewMatrix(s_camera->GetViewMatrix());

		glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, 0);
	}

	void Renderer::End()
	{

	}
}