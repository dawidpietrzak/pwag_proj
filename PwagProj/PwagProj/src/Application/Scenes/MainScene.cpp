#include "MainScene.h"

#include <Application/Application.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/Rendering/Mesh.h>
#include <Engine/Rendering/Material.h>

#include <Engine/Vendor/ImGui/imgui.h>

void MainScene::OnStart()
{
	m_cylinderGen.LoadBaseMeshData("assets/cylinder.obj");

	auto app = Application::Get();
	m_camera = app->GetCamera();

	auto assetManager = app->GetAssetManager();
	auto terrainMaterial = assetManager->GetMaterial("terrain_mat");
	auto terrainMesh = assetManager->GetMesh("terrain");
	m_terrain = std::make_unique<engine::Entity>(terrainMesh, terrainMaterial);

	auto defaultMaterial = assetManager->GetMaterial("default_mat");
	auto cylinderMesh = m_cylinderGen.CreateMesh(1.0f, 1.0f);
	m_cylinder = std::make_unique<engine::Entity>(cylinderMesh, defaultMaterial);
	m_cylinder->SetPosition({ 0, 4, 0 });
}

void MainScene::OnUIUpdate()
{
	ImGui::Begin("Hello, world!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::SliderFloat("Top Scale", &m_topScale, 0.1f, 1.0f);
	ImGui::SliderFloat("Bottom Scale", &m_bottomScale, 0.1f, 1.0f);
	if (ImGui::Button("Generuj cylinder"))
	{
		auto cylinderMesh = m_cylinderGen.CreateMesh(m_topScale, m_bottomScale);
		m_cylinder->DestroyMesh();
		m_cylinder->SetMesh(cylinderMesh);
	}
	ImGui::End();
}

void MainScene::OnUpdate(float deltaTime)
{
	engine::Renderer::Begin(m_camera);
	engine::Renderer::Draw(m_terrain);
	engine::Renderer::Draw(m_cylinder);
	engine::Renderer::End();
}
