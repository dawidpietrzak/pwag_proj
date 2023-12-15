#include "AppBase.h"

#include <GL/glew.h>
#include <Engine/Rendering/OpenGL/ShaderCompiler.h>
#include <Engine/Rendering/OpenGL/Viewport.h>
#include <Engine/Rendering/Renderer.h>

#include <Engine/Vendor/ImGui/imgui.h>
#include <Engine/Vendor/ImGui/imgui_impl_glfw.h>
#include <Engine/Vendor/ImGui/imgui_impl_opengl3.h>

namespace engine
{
	AppBase::AppBase()
	{
		m_assetManager = std::make_shared<AssetManager>(m_shaders);
	}

	void AppBase::Run()
	{
		OnInitialize();
		LoadInternalResources();

		OnStart();

		m_running = true;
		float deltaTime = 0.016f;
		while (m_running)
		{
			float startTime = glfwGetTime();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (m_currentScene)
			{
				m_currentScene->OnUpdate(deltaTime);

				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				m_currentScene->OnUIUpdate();

				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			}

			m_window.Update();
			deltaTime = glfwGetTime() - startTime;
		}

		Cleanup();
	}

	void AppBase::LoadInternalResources()
	{
		m_shaders["default"] = ShaderCompiler::CompileFromFile("shaders/default.fx");
		m_shaders["plant"] = ShaderCompiler::CompileFromFile("shaders/plant.fx");
		m_shaders["skybox"] = ShaderCompiler::CompileFromFile("shaders/skybox.fx");
	}

	void AppBase::Initialize(const AppSpec& appSpec)
	{
		glfwInit();
		m_window.Create(appSpec.WindowWidth, appSpec.WindowHeight);
		m_window.SetOnCloseHandler([&]() { m_running = false; });
		m_window.SetOnKeyboardHandler([this](KeyState keyState, int key) { OnKeyboard(keyState, key); });
		m_window.SetOnMouseButtonHandler([this](KeyState keyState, int button) { OnMouseButton(keyState, button); });
		m_window.SetOnMouseMoveHandler([this](int posX, int posY) { OnMouseMove(posX, posY); });
		glewInit();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(m_window.GetNativeWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");

		Viewport::Initialize(appSpec.WindowWidth, appSpec.WindowHeight);
		Renderer::Initialize();
	}

	void AppBase::Cleanup()
	{
		for (const auto& sceneKv : m_scenes)
			delete sceneKv.second;

		for (auto& shaderKv : m_shaders)
			shaderKv.second.Destroy();

		m_assetManager->Destroy();
		Renderer::Destroy();
	}

	void AppBase::SetCurrentScene(const std::string& sceneName)
	{
		m_currentScene = m_scenes[sceneName];
		m_currentScene->OnStart();
	}

	void AppBase::OnKeyboard(KeyState keyState, int key)
	{
		if (keyState == KeyState::Pressed)
		{
			m_keysPressed.insert(key);
		}
		else if (keyState == KeyState::Released)
		{
			m_keysPressed.erase(key);
		}

		m_currentScene->OnKeyboard(keyState, key);
	}

	void AppBase::OnMouseButton(KeyState keyState, int button)
	{
		if (keyState == KeyState::Pressed)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT)
				m_leftMouseButtonPressed = true;

			else if (button == GLFW_MOUSE_BUTTON_RIGHT)
				m_rightMouseButtonPressed = true;
		}
		else if (keyState == KeyState::Released)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT)
				m_leftMouseButtonPressed = false;

			else if (button == GLFW_MOUSE_BUTTON_RIGHT)
				m_rightMouseButtonPressed = false;
		}

		m_currentScene->OnMouseButton(keyState, button);
	}

	void AppBase::OnMouseMove(int posX, int posY)
	{
		m_currentScene->OnMouseMove(posX, posY);
	}
}