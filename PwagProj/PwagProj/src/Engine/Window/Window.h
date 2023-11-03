#pragma once

#include <GLFW/glfw3.h>

#include <functional>

namespace engine
{
	using CloseHandleFunc = std::function<void()>;

	class Window
	{
	public:
		void Create(int width, int height);
		void Update();

		GLFWwindow* GetNativeWindow() const { return m_window; }
		void SetOnCloseHandler(const CloseHandleFunc& closeHandleFunc) { m_closeHandleFunc = closeHandleFunc; }

	private:
		GLFWwindow* m_window;

		CloseHandleFunc m_closeHandleFunc = nullptr;

	private:
		static void WindowCloseCallback(GLFWwindow* nativeWindow);
	};
}
