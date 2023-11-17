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
		m_camera = std::make_shared<Camera>();
		m_assetManager = std::make_shared<AssetManager>(m_shaders);
	}

	void AppBase::Run()
	{
		OnInitialize();
		LoadInternalResources();

		OnStart();

		m_running = true;
		while (m_running)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (m_currentScene)
			{
				m_currentScene->OnUpdate(0.016f);

				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				m_currentScene->OnUIUpdate();

				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			}

			m_window.Update();
		}

		Cleanup();
	}

	void AppBase::LoadInternalResources()
	{
		m_shaders["default"] = ShaderCompiler::CompileFromFile("shaders/default.fx");
		m_shaders["plant"] = ShaderCompiler::CompileFromFile("shaders/plant.fx");
	}

	void AppBase::Initialize(const AppSpec& appSpec)
	{
		glfwInit();
		m_window.Create(appSpec.WindowWidth, appSpec.WindowHeight);
		m_window.SetOnCloseHandler([&]() { m_running = false; });
		glewInit();
		glEnable(GL_DEPTH_TEST);

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
}