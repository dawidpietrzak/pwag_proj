#include "MainScene.h"

#include <Application/Application.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/Rendering/Mesh.h>
#include <Engine/Rendering/Material.h>

#include <Engine/Vendor/ImGui/imgui.h>
#include "Engine/Vendor/ImGui/imgui_stdlib.h" // Make sure this path is correct
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
	m_cylinderGen.LoadBaseMeshData("assets/cylinder.obj");

	auto app = Application::Get();
	m_camera = app->GetCamera();

	auto assetManager = app->GetAssetManager();
	auto terrainMaterial = assetManager->GetMaterial("terrain_mat");
	auto terrainMesh = assetManager->GetMesh("terrain");
	m_terrain = std::make_unique<engine::Entity>(terrainMesh, terrainMaterial);

	auto defaultMaterial = assetManager->GetMaterial("default_mat");
	auto cylinderMesh = m_cylinderGen.CreateMesh(1.0f, 1.0f, 1.0f);
	m_cylinder = std::make_unique<engine::Entity>(cylinderMesh, defaultMaterial);
	m_cylinder->SetPosition({0, 4, 0});

	m_plantFactory = engine::PlantFactory();
	m_plantFactory.setMaterial("default_mat");

	rules.push_back(Rule{ "F", "FF-[&F^F^F]+[^F*&F&F*]<[^f*^f*&f*]" });
}

void MainScene::OnUIUpdate()
{
	ImGui::Begin("Hello, world!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	
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
		ImGui::PushID(i);
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

	static std::string lsystem_output;
	// Button to generate the L-System
	if (ImGui::Button("Generate")) {
		m_plantFactory.ClearPlants();
		auto grammar = std::make_shared<SimpleLSystemGrammar>(initialAxiom);
		m_plantFactory.setGrammar(grammar);

		for (const auto& rule : rules) {
			grammar->addRule(rule.symbol.c_str()[0], rule.replacement);
		}

		grammar->generate(generations);
		lsystem_output = grammar->getCurrentString();
		std::cout << grammar->getCurrentString();

		m_plantFactory.createPlant();
	}

	// Output

	// Provide a button to copy the text to the clipboard
	if (ImGui::Button("Copy output to clipboard")) {
		ImGui::SetClipboardText(lsystem_output.c_str());
	}
	
	if (ImGui::CollapsingHeader("L-System Output", ImGuiTreeNodeFlags_DefaultOpen))
	{
		// Wrap the text to the width of the child window
		ImGui::PushTextWrapPos();
		ImGui::TextUnformatted(lsystem_output.c_str());
		ImGui::PopTextWrapPos();
	}
	
	
}

void MainScene::OnUpdate(float deltaTime)
{
	engine::Renderer::Begin(m_camera);
	engine::Renderer::Draw(m_terrain);
	//engine::Renderer::Draw(m_cylinder);

	m_plantFactory.Draw();
	engine::Renderer::End();
}
