#pragma once

#include <Engine/Rendering/Camera.h>
#include <Engine/Rendering/Entity.h>

#include <memory>

namespace engine
{
	class Renderer
	{
	public:
		static void Begin(const std::shared_ptr<Camera>& camera);

		static void Draw(const Entity& entity);
		static void Draw(const std::unique_ptr<Entity>& entity);
		static void Draw(const std::shared_ptr<Entity>& entity);

		static void End();

	private:
		static std::shared_ptr<Camera> s_camera;
	};
}


