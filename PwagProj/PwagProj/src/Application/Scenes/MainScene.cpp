#include "MainScene.h"

#include <Application/Application.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/Vendor/ImGui/imgui.h>

void MainScene::OnStart()
{
	m_cylinderGen.LoadBaseMeshData("assets/cylinder.obj");

	auto app = Application::Get();
	m_camera = app->GetCamera();

	auto assetManager = app->GetAssetManager();
	auto groundTexture = assetManager->GetTexture("ground");
	m_terrainMaterial = assetManager->GetMaterial("terrain_mat");
	m_terrainMaterial.SetTexture(groundTexture);
	m_testMesh = assetManager->GetMesh("terrain");

	auto blobTexture = assetManager->GetTexture("blob");
	m_defaultMaterial = assetManager->GetMaterial("default_mat");
	m_defaultMaterial.SetTexture(blobTexture);
	m_cylinderMesh = m_cylinderGen.CreateMesh(1.0f, 1.0f);
}

void MainScene::OnUIUpdate()
{
	ImGui::Begin("Hello, world!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::SliderFloat("Top Scale", &m_topScale, 0.1f, 1.0f);
	ImGui::SliderFloat("Bottom Scale", &m_bottomScale, 0.1f, 1.0f);
	if (ImGui::Button("Generuj cylinder"))
	{
		m_cylinderMesh.Destroy();
		m_cylinderMesh = m_cylinderGen.CreateMesh(m_topScale, m_bottomScale);
	}
	ImGui::End();
}

void MainScene::OnUpdate(float deltaTime)
{
	engine::Renderer::Begin(m_camera);
	//engine::Renderer::Draw(m_testMesh, m_terrainMaterial);
	engine::Renderer::Draw(m_cylinderMesh, m_defaultMaterial);
	engine::Renderer::End();
}
