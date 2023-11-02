#include "AppBase.h"

#include <GL/glew.h>
#include <Engine/Rendering/OpenGL/ShaderCompiler.h>

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
				m_currentScene->OnUpdate(0.016f);

			m_window.Update();
		}

		Cleanup();
	}

	void AppBase::LoadInternalResources()
	{
		m_shaders["default"] = ShaderCompiler::CompileFromFile("shaders/default.fx");
	}

	void AppBase::Initialize(const AppSpec& appSpec)
	{
		glfwInit();
		m_window.Create(appSpec.WindowWidth, appSpec.WindowHeight);
		glewInit();
		glEnable(GL_DEPTH_TEST);
	}

	void AppBase::Cleanup()
	{
		for (const auto& sceneKv : m_scenes)
			delete sceneKv.second;

		for (auto& shaderKv : m_shaders)
			shaderKv.second.Destroy();

		m_assetManager->Destroy();
	}

	void AppBase::SetCurrentScene(const std::string& sceneName)
	{
		m_currentScene = m_scenes[sceneName];
		m_currentScene->OnStart();
	}
}