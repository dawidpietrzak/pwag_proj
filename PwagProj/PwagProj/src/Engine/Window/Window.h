#pragma once

#include <GLFW/glfw3.h>

#include <functional>

namespace engine
{
	enum class KeyState
	{
		Pressed,
		Released
	};

	using CloseHandleFunc = std::function<void()>;
	using KeyboardHandleFunc = std::function<void(KeyState keyState, int key)>;
	using MouseMoveHandleFunc = std::function<void(int posX, int posY)>;

	class Window
	{
	public:
		void Create(int width, int height);
		void Update();

		GLFWwindow* GetNativeWindow() const { return m_window; }

		void SetOnCloseHandler(CloseHandleFunc closeHandleFunc) { m_closeHandleFunc = closeHandleFunc; }
		void SetOnKeyboardHandler(KeyboardHandleFunc keyboardHandleFunc) { m_keyboardHandleFunc = keyboardHandleFunc; }
		void SetOnMouseMoveHandler(MouseMoveHandleFunc mouseMoveHandleFunc) { m_mouseMoveHandleFunc = mouseMoveHandleFunc; }

	private:
		GLFWwindow* m_window;

		CloseHandleFunc m_closeHandleFunc = nullptr;
		KeyboardHandleFunc m_keyboardHandleFunc = nullptr;
		MouseMoveHandleFunc m_mouseMoveHandleFunc = nullptr;

	private:
		static void WindowCloseCallback(GLFWwindow* nativeWindow);
		static void WindowKeyboardCallback(GLFWwindow* nativeWindow, int key, int scancode, int action, int mods);
		static void WindowMouseMoveCallback(GLFWwindow* nativeWindow, double posX, double posY);
	};
}
