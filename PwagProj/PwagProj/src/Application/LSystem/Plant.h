#pragma once
#include "Grammar/LSystemGrammar.h"
#include <Application/Application.h>
#include "Engine/Rendering/Mesh.h"
#include "Engine/Rendering/Renderer.h"
#include "Engine/Rendering/Material.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

#include <Application/Tools/CylinderGenerator.h>

namespace engine {
	class Plant {
	private:
		ILSystemGrammar* m_lSystem;
		Mesh m_baseMesh; // The base mesh to duplicate for each branch
		std::vector<std::shared_ptr<Entity>> m_branches; // Stores the transformed meshes for each branch
		std::string m_materialID;
		CylinderGenerator m_cylinderGen;
		std::shared_ptr<AssetManager> m_assetManager;

	public:
		Plant(ILSystemGrammar* lSystem, const Mesh& mesh, std::string& materialID);
		~Plant();

		void generateMeshInstances();
		void createBranch(float segmentLength, float segmentRadius, glm::mat4 currentTransform);
		void clearBranches();
		void draw();
	};

}
