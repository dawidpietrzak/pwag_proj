#include "Application.h"

#include <Application/Scenes/MainScene.h>


Application* Application::s_app = nullptr;

void Application::OnInitialize()
{
	engine::AppSpec appSpec = {};
	appSpec.WindowWidth = 1600;
	appSpec.WindowHeight = 900;
	appSpec.WindowTitle = "LSystem Presentation App";
	Initialize(appSpec);
}

void Application::OnStart()
{
	m_assetManager = GetAssetManager();
	LoadResources();
}

void Application::LoadResources()
{
	m_assetManager->CreateMaterial("default", "terrain_mat");
	m_assetManager->CreateMaterial("default", "default_mat");

	m_assetManager->LoadTextureFromFile("assets/blob.png", "blob");
	m_assetManager->LoadTextureFromFile("assets/ground.png", "ground");

	// m_assetManager->LoadMeshFromFile("assets/cube.obj", "cube");
	m_assetManager->LoadMeshFromFile("assets/terrain.obj", "terrain");

	AddScene("main_scene", new MainScene());
	SetCurrentScene("main_scene");
}
