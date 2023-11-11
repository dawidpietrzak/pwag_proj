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
	engine::Texture terrainTexture = m_assetManager->LoadTextureFromFile("assets/ground.png", "ground");
	engine::Texture blobTexture = m_assetManager->LoadTextureFromFile("assets/blob.png", "blob");

	engine::Material& terrainMaterial = m_assetManager->CreateMaterial("default", "terrain_mat");
	terrainMaterial.SetTexture(terrainTexture);

	engine::Material& defaultMaterial = m_assetManager->CreateMaterial("default", "default_mat");
	defaultMaterial.SetTexture(blobTexture);

	engine::Material& plantMaterial = m_assetManager->CreateMaterial("plant", "plant_mat");
	plantMaterial.SetTexture(blobTexture);

	m_assetManager->LoadMeshFromFile("assets/terrain.obj", "terrain");

	AddScene("main_scene", new MainScene());
	SetCurrentScene("main_scene");
}
