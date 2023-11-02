#include "Window.h"

namespace engine
{
	void Window::Create(int width, int height)
	{
		m_window = glfwCreateWindow(width, height, "Window title", NULL, NULL);
		glfwMakeContextCurrent(m_window);
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}
}