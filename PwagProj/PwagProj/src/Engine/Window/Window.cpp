#include "Window.h"

namespace engine
{
	void Window::WindowCloseCallback(GLFWwindow* nativeWindow)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(nativeWindow);
		if (window->m_closeHandleFunc)
			window->m_closeHandleFunc();
	}

	void Window::Create(int width, int height)
	{
		m_window = glfwCreateWindow(width, height, "Window title", NULL, NULL);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetWindowCloseCallback(m_window, WindowCloseCallback);
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}
}