#pragma once

#include <GLFW/glfw3.h>

namespace engine
{
	class Window
	{
	public:
		void Create(int width, int height);
		void Update();

	private:
		GLFWwindow* m_window;
	};
}
