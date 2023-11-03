#include "MainScene.h"

#include <Application/Application.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/Vendor/ImGui/imgui.h>

void MainScene::OnStart()
{
	auto app = Application::Get();
	m_camera = app->GetCamera();

	auto assetManager = app->GetAssetManager();
	auto groundTexture = assetManager->GetTexture("ground");
	m_material = assetManager->GetMaterial("default_mat");
	m_material.SetTexture(groundTexture);
	m_testMesh = assetManager->GetMesh("terrain");
}

void MainScene::OnUIUpdate()
{
	ImGui::Begin("Hello, world!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void MainScene::OnUpdate(float deltaTime)
{
	engine::Renderer::Begin(m_camera);
	engine::Renderer::Draw(m_testMesh, m_material);
	engine::Renderer::End();
}
