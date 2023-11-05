#pragma once

#include <vector>
#include <string>

#include <Engine/Tools/MeshTools.h>

class CylinderGenerator
{
public:
	void LoadBaseMeshData(const std::string& filePath);
	engine::Mesh CreateMesh(float topScale, float bottomScale);

private:
	std::vector<GLfloat> m_vertices;
	std::vector<GLuint> m_indices;
};

