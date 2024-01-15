#include "ForestGenerator.h"
#include <Engine/Rendering/Renderer.h>
#include <iostream>
#include <cmath> // Include the cmath library

ForestGenerator::ForestGenerator()
{
	
}

void ForestGenerator::init(const std::string& baseMeshPath, engine::Material& treeMaterial)
{
	m_treeMeshGenerator.LoadBaseMeshData(baseMeshPath);
	m_treeMaterial = treeMaterial;
}

void ForestGenerator::populateForest(int treeCount)
{
	if (m_distributionStrategy == nullptr)
		return;

	
	auto positions = m_distributionStrategy->GetPositions(treeCount);

	m_treeEntities.clear();
	for (int i = 0; i < treeCount; i++) {
		std::shared_ptr<Plant> plant_ptr = std::make_shared<Plant>();
		plant_ptr->entity = std::make_shared<engine::Entity>();
		m_treeEntities.push_back(plant_ptr);
		plant_ptr->entity->SetPosition(origin+positions[i]);
	}
}

void ForestGenerator::generate(int iterations, const std::shared_ptr<ILSystemGrammar>& lSystemGrammarTemplate, bool forceRecalculation) {
	for (auto& plantEntity : m_treeEntities) {
		// Only generate for plants with empty generationStrings
		if (!plantEntity->generationSentence.empty() && !forceRecalculation)
			continue;

		if (plantEntity->entity->IsCreated())
			plantEntity->entity->DestroyMesh();

		plantEntity->generationSentence.clear(); // Clear existing strings
		std::shared_ptr<ILSystemGrammar> grammarInstance = lSystemGrammarTemplate->clone();
		grammarInstance->generate(iterations);
		plantEntity->generationSentence = grammarInstance->getCurrentSymbols();


	}
}

//float exampleGrowthFunction(const float& t, const float& timeForSingleGeneration, const int& maxGenerations) {
//	// Example implementation (e.g., linear growth)
//	//https://algorithmicbotany.org/papers/animdev.sig93.pdf
//	float xmin = 0.0f;
//	float xmax = 1.0f;
//	float dx = xmax - xmin;
//	float T = timeForSingleGeneration * maxGenerations;
//	return -2*dx/pow(T, 3)*pow(t, 3) + 3 * dx / pow(T, 2) * pow(t, 2) + xmin;
//}

static float exampleGrowthFunction(float t, float timeForSingleGeneration, int maxGenerations) {
	float T = timeForSingleGeneration * maxGenerations;
	return 1 - std::pow(1 - t / T, 2);
}

void ForestGenerator::setTime(float time, float timeForSingleGeneration, int maxGenerations)
{
	for (auto& plantEntity : m_treeEntities) {
		if (plantEntity->generationSentence.empty())
		{
			std::cerr << "Generation string is empty" << std::endl;
			continue;
		}
		if (plantEntity->entity->IsCreated())
			plantEntity->entity->DestroyMesh();

		std::vector<Symbol> lSystemOutput = plantEntity->generationSentence;
		// Use the L-system output to create plant segments
		float growFactor = exampleGrowthFunction(time, timeForSingleGeneration, maxGenerations);
		auto plantSegments = PlantFactory::CreatePlant(lSystemOutput, growFactor, segmentLength, angle, bottomScale, topScale, time, timeForSingleGeneration, maxGenerations);
		if (plantSegments.size() == 0)
			continue;

		auto plantMesh = m_treeMeshGenerator.GenerateMesh(plantSegments);
		plantEntity->entity->Create(plantMesh, m_treeMaterial);
	}
}

void ForestGenerator::drawTrees() {
	for (const auto& plantEntity : m_treeEntities)
		if (plantEntity->entity->IsCreated())
		{
			engine::Renderer::Draw(plantEntity->entity);
		}
}