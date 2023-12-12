#pragma once

#include <GL/glew.h>
#include <Engine/Window/Window.h>

namespace engine
{
	class Scene
	{
	public:
		virtual void OnStart() = 0;
		virtual void OnUpdate(float deltaTime) = 0;
		virtual void OnUIUpdate() = 0;

		virtual void OnKeyboard(KeyState keyState, int key) { }
		virtual void OnMouseMove(int posX, int posY) { }

		virtual void OnMouseButton(KeyState keyState, int button) { }
	};
}



