#pragma once

#include <Engine/Rendering/Camera.h>
#include <Engine/Rendering/Mesh.h>
#include <Engine/Rendering/Material.h>

#include <memory>

namespace engine
{
	class Renderer
	{
	public:
		static void Begin(const std::shared_ptr<Camera>& camera);
		static void Draw(Mesh mesh, Material material);
		static void End();

	private:
		static std::shared_ptr<Camera> s_camera;
	};
}


