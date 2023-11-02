#pragma once

#include <Engine/Rendering/Mesh.h>

#include <string>
#include <fstream>

namespace engine
{
	class MeshTools
	{
	public:
		static Mesh LoadMeshFromObjFile(const std::string& filePath);

	private:
		static void ParseObjFile(std::ifstream& inputFile, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	};
}