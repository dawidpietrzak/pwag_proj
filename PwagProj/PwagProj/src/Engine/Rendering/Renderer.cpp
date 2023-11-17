#include "Renderer.h"

#include <GLM/gtc/matrix_transform.hpp>
#include <Engine/Rendering/OpenGL/Viewport.h>

namespace engine
{
	static const glm::vec3 LightPosition = { -15, 20, -15 };

	std::shared_ptr<Camera> Renderer::s_camera;
	std::vector<Entity*> Renderer::s_entitiesToDraw;
	Framebuffer Renderer::s_framebuffer;
	glm::mat4 Renderer::s_lightProjectionMatrix;
	glm::mat4 Renderer::s_lightViewMatrix;

	void Renderer::Initialize()
	{
		s_lightProjectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 1000.0f);
		s_lightViewMatrix = glm::lookAt(LightPosition, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		s_framebuffer.CreateDepthBuffer(1024, 1024);
	}

	void Renderer::Destroy()
	{
		s_framebuffer.Destroy();
	}

	void Renderer::Begin(const std::shared_ptr<Camera>& camera)
	{
		s_camera = camera;
		s_entitiesToDraw.clear();
	}

	void Renderer::Draw(const Entity& entity)
	{
		s_entitiesToDraw.push_back((Entity*)&entity);
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
		RunShadowPass();
		DrawScene();
	}

	void Renderer::RunShadowPass()
	{
		Viewport::SetFromFramebufferSize(s_framebuffer);
		s_framebuffer.Bind();

		glClear(GL_DEPTH_BUFFER_BIT);

		for (const auto entity : s_entitiesToDraw)
		{
			entity->Bind();

			Material material = entity->GetMaterial();
			material.SetProjectionMatrix(s_lightProjectionMatrix);
			material.SetViewMatrix(s_lightViewMatrix);
			material.SetModelMatrix(entity->GetTransformMatrix());
			material.SetIsShadowPass(true);

			Mesh mesh = entity->GetMesh();
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

		s_framebuffer.Unbind();
		Viewport::SetDefaultSize();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::DrawScene()
	{
		for (const auto entity : s_entitiesToDraw)
		{
			entity->Bind();

			Material& material = entity->GetMaterial();
			material.SetProjectionMatrix(s_camera->GetProjectionMatrix());
			material.SetViewMatrix(s_camera->GetViewMatrix());
			material.SetModelMatrix(entity->GetTransformMatrix());
			material.SetLightProjectionMatrix(s_lightProjectionMatrix);
			material.SetLightViewMatrix(s_lightViewMatrix);
			material.SetLightPosition(LightPosition);
			material.SetDepthTexture(s_framebuffer.GetTexture());
			material.SetIsShadowPass(false);

			Mesh mesh = entity->GetMesh();
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
	}
}