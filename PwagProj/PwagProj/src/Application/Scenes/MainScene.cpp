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
#include <Application/LSystem/Grammar/ProbabilisticLSystemGrammar.h>
#include <Application/LSystem/Grammar/TextLSystemGrammar.h>



struct Rule {
    std::string symbol;
    std::string replacement;
    float probability; // Added probability field
};

// Vector to hold all the rules
std::vector<Rule> rules;

void MainScene::OnStart()
{

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

	auto skyboxMesh = assetManager->GetMesh("skybox");
	auto skyboxMaterial = assetManager->GetMaterial("skybox_mat");
	m_skyboxEntity.Create(skyboxMesh, skyboxMaterial);
	
	rules.push_back(Rule{ "F", "(F(+F)[>+F])" });

	m_forestGenerator.init("assets/log.obj", m_plantMaterial);
	glm::vec2 area = glm::vec2(20, 20);
	int16_t gridSubdivision = 10;
	std::shared_ptr<IDistributionStrategy> gridDistribution = std::make_shared<GridRandomDistributionStrategy>(area, gridSubdivision);
	gridDistribution->RecalculatePositions();
	m_forestGenerator.SetDistributionStrategy(gridDistribution);
	m_forestGenerator.populateForest(5);

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
	static int maxGenerations = 2; // Number of maxGenerations to generate
	static int treeCount = 5;
	static int lSystemType = 0; // 0 for Simple, 1 for Probabilistic
	static const char* lSystemTypes[] = { "Simple L-System", "Probabilistic L-System"}; //, "FromText[unimplemented]" 
	static float framesPerGeneration = 100;
	static int time = 0;

	static int plantDistributionType = 0;
	static const char* plantDistributionTypes[] = { "RandomGrid", "TerrainBasedRandomGrid[unimplemented]" };

	// Buffer for input text
	static char textGrammarInputBuffer[1024] = "";


	auto RegenerateForest = [&](bool forceRecalculation = false) {
		if (lSystemType == 0) {
			m_lSystemGrammar = std::make_shared<SimpleLSystemGrammar>();
		}
		else if (lSystemType == 1) {
			m_lSystemGrammar = std::make_shared<ProbabilisticLSystemGrammar>();
		}
		else if (lSystemType == 2) {
			m_lSystemGrammar = std::make_shared<TextLSystemGrammar>();
		}

		m_lSystemGrammar->setCurrentString(initialAxiom);
		for (const auto& rule : rules) {
			if (lSystemType == 0) {
				m_lSystemGrammar->addRule(rule.symbol.c_str()[0], rule.replacement);
			}
			else if (lSystemType == 1) {
				std::shared_ptr<ProbabilisticLSystemGrammar> probabilisticLSystemGrammar = std::dynamic_pointer_cast<ProbabilisticLSystemGrammar>(m_lSystemGrammar);
				if (probabilisticLSystemGrammar)
					probabilisticLSystemGrammar->addRule(rule.symbol.c_str()[0], rule.replacement, rule.probability);
			}
			else if (lSystemType == 2) {
				std::shared_ptr<TextLSystemGrammar> textLSystemGrammar = std::dynamic_pointer_cast<TextLSystemGrammar>(m_lSystemGrammar);
				if (textLSystemGrammar) {
					std::string inputText(textGrammarInputBuffer); // Convert to std::string
					textLSystemGrammar->parseText(inputText); // Process the text
				}
					
			}

		}

		m_forestGenerator.generate(maxGenerations, m_lSystemGrammar, forceRecalculation);
		m_forestGenerator.setTime(time, framesPerGeneration, maxGenerations);
	};

	auto PopulateForest = [&]() {
		if (plantDistributionType == 0) {
			static glm::vec2 area = glm::vec2(20, 20);
			static int16_t gridSubdivision = 10;
			std::shared_ptr<IDistributionStrategy> gridDistribution = std::make_shared<GridRandomDistributionStrategy>(area, gridSubdivision);
			gridDistribution->RecalculatePositions();
			m_forestGenerator.SetDistributionStrategy(gridDistribution);
			m_forestGenerator.populateForest(treeCount);
		}
	};


	if (ImGui::Combo("Plant Distribution Algorithm", &plantDistributionType, plantDistributionTypes, IM_ARRAYSIZE(plantDistributionTypes))) {

		PopulateForest();
	}
	if (ImGui::SliderInt("Tree Count", &treeCount, 0, 20)) {
		m_forestGenerator.populateForest(treeCount);
		RegenerateForest();
	}

	ImGui::Spacing();

	static int plantTemplate = 0;
	static const char* plantTemplateTypes[] = { "Custom", "Plant1"};

	
	
	if (ImGui::InputInt("Max Generations", &maxGenerations))
		RegenerateForest(true);
	if (ImGui::SliderInt("Current generation", &time, 0, maxGenerations* framesPerGeneration)) {
		m_forestGenerator.setTime(time, framesPerGeneration, maxGenerations);
	}
	

	if (ImGui::Combo("Template", &plantTemplate, plantTemplateTypes, IM_ARRAYSIZE(plantTemplateTypes))) {

		if (plantTemplate == 1) {
			rules.clear();

			lSystemType = 1;
			m_forestGenerator.segmentLength = 0.5f;
			m_forestGenerator.angle = 33;
			m_forestGenerator.topScale = 0.075;
			m_forestGenerator.bottomScale = 0.1f;


			rules.push_back(Rule{ "F", "(F[&++F]F[^--F])", 0.30 });
			rules.push_back(Rule{ "F", "(F[&+>F])", 0.30 });
			rules.push_back(Rule{ "F", "(F[^-F])", 0.30});
			rules.push_back(Rule{ "F", "F(F)", 0.10 });

			RegenerateForest(true);
		}

	}



	ImGui::Combo("L-System Type", &lSystemType, lSystemTypes, IM_ARRAYSIZE(lSystemTypes));

	if (ImGui::CollapsingHeader("Lsystem Paramethers")) {
		if (ImGui::SliderFloat("Length", &m_forestGenerator.segmentLength, 0.01f, 3.0f)
			|| ImGui::SliderFloat("Angle", &m_forestGenerator.angle, 0.0f, 180.0f)
			|| ImGui::SliderFloat("TopScale", &m_forestGenerator.topScale, 0.01f, 0.5f)
			|| ImGui::SliderFloat("BottomScale", &m_forestGenerator.bottomScale, 0.01f, 0.5f)) {
			plantTemplate = 0;
			RegenerateForest(false);
		}
		ImGui::Separator();
	}

	ImGui::InputText("Initial Axiom", &initialAxiom);
	ImGui::Text("Rules");
	ImGui::Separator();

	for (size_t i = 0; i < rules.size(); ++i) {

		if (lSystemType == 0 || lSystemType == 1)
		{
			ImGui::PushID((int)i);
			ImGui::SetNextItemWidth(50);
			if (ImGui::InputText("##Symbol", &rules[i].symbol))	plantTemplate = 0;

			// Conditional probability field for Probabilistic L-System
			if (lSystemType == 1) {
				ImGui::SameLine();
				ImGui::SetNextItemWidth(60); // Adjusted width
				ImGui::DragFloat("##Probability", &rules[i].probability, 0.0f, 1.0f);
			}

			ImGui::SameLine();
			float availableWidth = ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(" - ").x - ImGui::GetStyle().ItemSpacing.x;
			ImGui::SetNextItemWidth(availableWidth); // Adjusted width

			if (ImGui::InputText("##Replacement", &rules[i].replacement)) plantTemplate = 0;


			ImGui::SameLine();
			ImGui::SetNextItemWidth(30);
			std::string button_label = "-##";
			if (ImGui::Button(button_label.c_str())) {
				rules.erase(rules.begin() + i);
				ImGui::PopID();
				continue;
			}
			ImGui::PopID();
		}
		else if (lSystemType == 2)
		{
			if (ImGui::InputText("##Input text", textGrammarInputBuffer, IM_ARRAYSIZE(textGrammarInputBuffer))){}
		}
		
	}

	if (ImGui::Button("Add Rule")) {
		rules.push_back(Rule{ "\0", "", 0.0f }); // Initialize probability to 0.0
		plantTemplate = 0;
	}

	static std::string lSystemOutput;
	if (ImGui::Button("Regenerate"))
	{
		RegenerateForest(true);
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
	engine::Renderer::DrawSkybox(m_skyboxEntity);
	engine::Renderer::Draw(m_terrain);
	engine::Renderer::Draw(m_cubeEntity);

	m_forestGenerator.drawTrees();

	engine::Renderer::End();
}


void MainScene::OnMouseMove(int posX, int posY)
{
	if (Application::Get()->IsRightMouseButtonPressed())
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
}

void MainScene::OnMouseButton(engine::KeyState keyState, int button)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && keyState == engine::KeyState::Released)
	{
		m_lastMouseX = -1;
		m_lastMouseY = -1;
	}
}