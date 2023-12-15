#pragma once

#include "PlantFactory.h"
#include "Application/Tools/PlantInstancedMeshGen.h"
#include <Engine/Rendering/Entity.h>

#include <string>
#include "Distribution/DistributionStrategy.h"

struct Plant {
	std::shared_ptr<engine::Entity> entity;
	std::vector<std::string> generationStrings;
};

class ForestGenerator
{
public:
	ForestGenerator();
	void init(const std::string& baseMeshPath, engine::Material& treeMaterial);
	void populateForest(int treeCount);
	void generate(int iterations, const std::shared_ptr<ILSystemGrammar>& lSystemGrammar, bool forceRecalculation = false);
	inline void SetDistributionStrategy(const std::shared_ptr<IDistributionStrategy>& strategy) { m_distributionStrategy = strategy; };
	void setTime(float time, float timeForSingleGeneration, int maxGenerations);
	void drawTrees();

	float segmentLength = 1.0f;
	float angle = 25.0f;
	float bottomScale = 0.1f;
	float topScale = 0.1f;
private:
	PlantInstancedMeshGen m_treeMeshGenerator;
	std::shared_ptr<IDistributionStrategy> m_distributionStrategy;
	std::vector<std::shared_ptr<Plant>> m_treeEntities;
	engine::Material m_treeMaterial;
	glm::vec3 origin = glm::vec3(-10, 1, -10); // temporaty solution
	
};

