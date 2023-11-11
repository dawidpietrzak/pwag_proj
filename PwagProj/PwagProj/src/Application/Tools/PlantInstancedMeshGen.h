#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>

#include <Engine/Rendering/Mesh.h>
#include <Application/LSystem/PlantFactory.h>

class PlantInstancedMeshGen
{
public:
	void LoadBaseMeshData(const std::string& filePath);
	engine::Mesh GenerateMesh(const std::vector<PlantSegment>& plantSegments) const;

private:
	std::vector<GLfloat> m_vertices;
	std::vector<GLuint> m_indices;
};