#pragma once

#include <Engine/Rendering/OpenGL/Framebuffer.h>
#include <Engine/Rendering/Camera.h>
#include <Engine/Rendering/Entity.h>

#include <memory>
#include <vector>

namespace engine
{
	class Renderer
	{
	public:
		static void Initialize();
		static void Destroy();

		static void Begin(const std::shared_ptr<Camera>& camera);

		static void Draw(const Entity& entity);
		static void Draw(const std::unique_ptr<Entity>& entity);
		static void Draw(const std::shared_ptr<Entity>& entity);

		static void End();

	private:
		static std::vector<Entity*> s_entitiesToDraw;
		static std::shared_ptr<Camera> s_camera;

		static Framebuffer s_framebuffer;
		static glm::mat4 s_lightProjectionMatrix;
		static glm::mat4 s_lightViewMatrix;

	private:
		static void RunShadowPass();
		static void DrawScene();
	};
}


