#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <memory>

#include <Engine/Rendering/OpenGL/Shader.h>
#include <Engine/Rendering/Camera.h>
#include <Engine/Window/Window.h>
#include <Engine/Scenes/Scene.h>
#include <Engine/Assets/AssetManager.h>


namespace engine
{
	struct AppSpec
	{
		int WindowWidth;
		int WindowHeight;
		const char* WindowTitle;
	};

	class AppBase
	{
	public:
		AppBase();

		void Run();

		virtual void OnInitialize() { }
		virtual void OnStart() { }

		void SetCurrentScene(const std::string& sceneName);

		std::shared_ptr<AssetManager> GetAssetManager() const { return m_assetManager; }

		bool IsKeyPressed(int key) const { return m_keysPressed.find(key) != m_keysPressed.end(); }

	protected:
		void Initialize(const AppSpec& appSpec);
		void AddScene(const std::string& sceneName, Scene* scene) { m_scenes[sceneName] = scene; }

	private:
		Window m_window;
		bool m_running = false;
		std::unordered_set<int> m_keysPressed;

		std::unordered_map<std::string, Scene*> m_scenes;
		Scene* m_currentScene = nullptr;

		std::unordered_map<std::string, Shader> m_shaders;

		std::shared_ptr<AssetManager> m_assetManager;

	private:
		void LoadInternalResources();
		void Cleanup();

		void OnKeyboard(KeyState keyState, int key);
		void OnMouseMove(int posX, int posY);
	};
}