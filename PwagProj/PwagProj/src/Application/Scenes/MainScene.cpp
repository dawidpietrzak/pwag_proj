#include "MainScene.h"

#include <Application/Application.h>
#include <Application/LSystem/PlantFactory.h>

#include <Engine/Rendering/Renderer.h>
#include <Engine/Rendering/Mesh.h>
#include <Engine/Rendering/Material.h>

#include <Engine/Vendor/ImGui/imgui.h>
#include <Engine/Vendor/ImGui/imgui_stdlib.h>
#include <iostream>

#include <vector>
#include <string>



struct Rule {
	std::string symbol;
	std::string replacement;
};

// Vector to hold all the rules
std::vector<Rule> rules;

void MainScene::OnStart()
{
	m_plantInstancedMeshGen.LoadBaseMeshData("assets/cylinderTransformBottom.obj");

	auto app = Application::Get();
	m_camera = std::make_shared<engine::Camera>();

	auto assetManager = app->GetAssetManager();
	auto terrainMaterial = assetManager->GetMaterial("terrain_mat");
	auto terrainMesh = assetManager->GetMesh("terrain");
	m_terrain = std::make_unique<engine::Entity>(terrainMesh, terrainMaterial);

	m_plantMaterial = assetManager->GetMaterial("plant_mat");
	auto cubeMesh = assetManager->GetMesh("cube");
	
	auto defaultMaterial = assetManager->GetMaterial("default_mat");
	m_cubeEntity.Create(cubeMesh, defaultMaterial);
	m_cubeEntity.SetPosition({ 0, 2, 0 });
	
	rules.push_back(Rule{ "F", "FF-[&F^F^F]+[^F*&F&F*]<[^f*^f*&f*]" });
	m_plantEntity.SetPosition({ 0, 1, 0 });
}

void MainScene::OnUIUpdate()
{
	ImGui::Begin("Hello, world!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Image((ImTextureID)engine::Renderer::GetFramebuffer().GetTexture().GetId(), { 128, 128 });

	OnLSystemUIUpdate();

	ImGui::End();
}

void MainScene::OnLSystemUIUpdate()
{
	ImGui::Text("Lsystem");
	ImGui::Separator();
	static std::string initialAxiom = "F";
	static int generations = 2; // Number of generations to generate

	//ImGui::SliderFloat("Top Scale", &m_topScale, 0.1f, 1.0f);
	//ImGui::SliderFloat("Bottom Scale", &m_bottomScale, 0.1f, 1.0f);

	ImGui::InputText("Initial Axiom", &initialAxiom);
	ImGui::InputInt("Generations", &generations);
	ImGui::Text("Rules");
	ImGui::Separator();
	// Iterate over all rules and create an input text field for each

	for (size_t i = 0; i < rules.size(); ++i) {
		ImGui::PushID((int)i);
		ImGui::SetNextItemWidth(50);
		if (ImGui::InputText("##Symbol", &rules[i].symbol)) {
			rules[i].symbol = rules[i].symbol.empty() ? '\0' : rules[i].symbol.front();
		}
		ImGui::SameLine();
		float availableWidth = ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(" - ").x - ImGui::GetStyle().ItemSpacing.x;
		ImGui::SetNextItemWidth(availableWidth);
		ImGui::InputText("##Replacement", &rules[i].replacement);

		ImGui::SameLine();
		ImGui::SetNextItemWidth(30);
		// Add a delete button for each rule
		std::string button_label = "-##";
		if (ImGui::Button(button_label.c_str())) {
			rules.erase(rules.begin() + i);
			ImGui::PopID(); // PopID before the continue to match the PushID call
			continue; // skip the rest of the loop as the current element is now deleted
		}

		ImGui::PopID();
	}

	// Button to add a new rule
	if (ImGui::Button("Add Rule")) {
		rules.push_back(Rule{ "\0", "" });
	}

	static std::string lSystemOutput;
	if (ImGui::Button("Generate"))
	{
		if (m_plantEntity.IsCreated())
		{
			m_plantEntity.DestroyMesh();
		}

		m_lSystemGrammar = std::make_unique<SimpleLSystemGrammar>();
		m_lSystemGrammar->setCurrentString(initialAxiom);
		for (const auto& rule : rules)
			m_lSystemGrammar->addRule(rule.symbol.c_str()[0], rule.replacement);

		m_lSystemGrammar->generate(generations);
		lSystemOutput = m_lSystemGrammar->getCurrentString();
		auto plantSegments = PlantFactory::CreatePlant(lSystemOutput);
		auto plantMesh = m_plantInstancedMeshGen.GenerateMesh(plantSegments);
		m_plantEntity.Create(plantMesh, m_plantMaterial);
	}

	// Provide a button to copy the text to the clipboard
	if (ImGui::Button("Copy output to clipboard")) {
		ImGui::SetClipboardText(lSystemOutput.c_str());
	}
	
	if (ImGui::CollapsingHeader("L-System Output", ImGuiTreeNodeFlags_DefaultOpen))
	{
		// Wrap the text to the width of the child window
		ImGui::PushTextWrapPos();
		if (lSystemOutput.size() < 1000)
		{
			ImGui::TextUnformatted(lSystemOutput.c_str());
		}
		else
		{
			ImGui::TextUnformatted("Output too long");
		}
		
		ImGui::PopTextWrapPos();
	}
	
	
}

void MainScene::OnUpdate(float deltaTime)
{
	auto app = Application::Get();
	const float moveSpeed = deltaTime * 12.0f;
	if (app->IsKeyPressed(GLFW_KEY_W))
	{
		m_camera->MoveForward(moveSpeed);
	}
	else if (app->IsKeyPressed(GLFW_KEY_S))
	{
		m_camera->MoveBackward(moveSpeed);
	}

	if (app->IsKeyPressed(GLFW_KEY_A))
	{
		m_camera->MoveLeft(moveSpeed);
	}
	else if (app->IsKeyPressed(GLFW_KEY_D))
	{
		m_camera->MoveRight(moveSpeed);
	}

	if (app->IsKeyPressed(GLFW_KEY_SPACE))
	{
		m_camera->MoveUp(moveSpeed);
	}
	else if (app->IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		m_camera->MoveDown(moveSpeed);
	}

	m_timer += deltaTime;

	engine::Renderer::Begin(m_camera);
	engine::Renderer::SetLightPosition({ 15 * cosf(m_timer * 0.5f), 20, 15 * sinf(m_timer * 0.5f) });
	engine::Renderer::Draw(m_terrain);
	engine::Renderer::Draw(m_cubeEntity);
	if (m_plantEntity.IsCreated())
	{
		engine::Renderer::Draw(m_plantEntity);
	}
	engine::Renderer::End();
}


void MainScene::OnMouseMove(int posX, int posY)
{
	int deltaX = 0;
	int deltaY = 0;

	if (m_lastMouseX != -1 && m_lastMouseY != -1)
	{
		deltaX = (int)(posX - m_lastMouseX);
		deltaY = (int)(posY - m_lastMouseY);
	}

	m_lastMouseX = posX;
	m_lastMouseY = posY;

	m_camera->Rotate({ deltaX * 0.3f, deltaY * 0.3f, 0 });
}
