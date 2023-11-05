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

		static void LoadMeshDataFromObjFile(const std::string& filePath, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
		static Mesh CreateMeshFromRawData(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);

	private:
		static void ParseObjFile(std::ifstream& inputFile, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
	};
}