#include "Window.h"

namespace engine
{
	void Window::WindowCloseCallback(GLFWwindow* nativeWindow)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(nativeWindow);
		if (window->m_closeHandleFunc)
			window->m_closeHandleFunc();
	}

	void Window::WindowKeyboardCallback(GLFWwindow* nativeWindow, int key, int scancode, int action, int mods)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(nativeWindow);

		KeyState keyState;
		switch (action)
		{
			case GLFW_PRESS: keyState = KeyState::Pressed; break;
			case GLFW_RELEASE: keyState = KeyState::Released; break;
			default: return;
		}

		if (window->m_keyboardHandleFunc)
			window->m_keyboardHandleFunc(keyState, key);
	}

	void Window::WindowMouseMoveCallback(GLFWwindow* nativeWindow, double posX, double posY)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(nativeWindow);
		if (window->m_mouseMoveHandleFunc)
			window->m_mouseMoveHandleFunc((int)posX, (int)posY);
	}

	void Window::Create(int width, int height)
	{
		m_window = glfwCreateWindow(width, height, "Window title", NULL, NULL);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetWindowCloseCallback(m_window, WindowCloseCallback);
		glfwSetKeyCallback(m_window, WindowKeyboardCallback);
		glfwSetCursorPosCallback(m_window, WindowMouseMoveCallback);
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}
}