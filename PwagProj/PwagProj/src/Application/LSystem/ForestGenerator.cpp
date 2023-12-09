#include "ForestGenerator.h"
#include <Engine/Rendering/Renderer.h>
#include <iostream>

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
	for (int i{ 0 }; i < treeCount; i++) {
		std::shared_ptr<Plant> plant_ptr = std::make_shared<Plant>();
		plant_ptr->entity = std::make_shared<engine::Entity>();
		m_treeEntities.push_back(plant_ptr);

		std::cout << positions[i].x << " " << positions[i].y << " " << positions[i].z << std::endl;
		plant_ptr->entity->SetPosition(origin+positions[i]);
	}
}

void ForestGenerator::generate(int iterations, std::shared_ptr<ILSystemGrammar> lSystemGrammarTemplate, bool forceRecalculation) {
	for (auto& plantEntity : m_treeEntities) {
		// Only generate for plants with empty generationStrings
		if (!plantEntity->generationStrings.empty() && !forceRecalculation)
			continue;

		if (plantEntity->entity->IsCreated())
			plantEntity->entity->DestroyMesh();

		plantEntity->generationStrings.clear(); // Clear existing strings
		std::shared_ptr<ILSystemGrammar> grammarInstance = lSystemGrammarTemplate->clone();
		for (int i = 0; i <= iterations; ++i) {
			grammarInstance->generate(i == 0 ? 0 : 1);
			plantEntity->generationStrings.push_back(grammarInstance->getCurrentString());
			std::cout << "generate" << std::endl;
		}
	}
}

void ForestGenerator::setGeneration(int generation)
{
	for (auto& plantEntity : m_treeEntities) {
		if (plantEntity->generationStrings.empty())
			continue;

		if (plantEntity->entity->IsCreated())
			plantEntity->entity->DestroyMesh();

		std::string lSystemOutput = plantEntity->generationStrings[generation];
		// Use the L-system output to create plant segments
		auto plantSegments = PlantFactory::CreatePlant(lSystemOutput, segmentLength, angle, bottomScale, topScale);
		auto plantMesh = m_treeMeshGenerator.GenerateMesh(plantSegments);
		plantEntity->entity->Create(plantMesh, m_treeMaterial);
	}
}

void ForestGenerator::drawTrees() {
	for (auto plantEntity : m_treeEntities)
		if (plantEntity->entity->IsCreated())
		{
			engine::Renderer::Draw(plantEntity->entity);
		}
}