#include "MeshTools.h"

#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>

#include <Engine/Tools/StringTools.h>

namespace engine
{
	struct Vec3f
	{
		float X, Y, Z;
	};

	struct Vec2f
	{
		float X, Y;
	};

	Mesh MeshTools::LoadMeshFromObjFile(const std::string& filePath)
	{
		std::ifstream inputFile(filePath, std::ios::in);
		if (!inputFile.is_open())
			throw std::exception("Could not open mesh .obj file");

		std::vector<GLfloat> vertices;
		std::vector<GLuint> indices;
		ParseObjFile(inputFile, vertices, indices);

		inputFile.close();

		VertexBuffer vertexBuffer;
		vertexBuffer.Create(vertices);

		VertexAttrib vertexAttrib;
		vertexAttrib.Create({
			3, // Position 3D
			2, // TexCoords 2D
			3, // Normal 3D
		});

		IndexBuffer indexBuffer;
		indexBuffer.Create(indices);

		Mesh mesh;
		mesh.Create(vertexBuffer, vertexAttrib, indexBuffer);
		return mesh;
	}

	void MeshTools::ParseObjFile(std::ifstream& inputFile, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices)
	{
		std::vector<Vec3f> positions;
		std::vector<Vec2f> texCoords;
		std::vector<Vec3f> normals;

		std::string line;
		size_t currentIndex = 0;

		std::unordered_map<std::string, uint32_t> faceIndices;

		while (std::getline(inputFile, line))
		{
			if (line.empty())
				continue;

			if (line[0] == '#')
				continue;

			std::istringstream is(line);
			std::string command;

			is >> command;

			// Vertex position
			if (command == "v")
			{
				float x, y, z;
				is >> x >> y >> z;
				positions.push_back({ x, y, z });
			}

			// Texture coords
			else if (command == "vt")
			{
				float x, y;
				is >> x >> y;
				texCoords.push_back({ x, y });
			}

			// Normal
			else if (command == "vn")
			{
				float x, y, z;
				is >> x >> y >> z;
				normals.push_back({ x, y, z });
			}

			// Face
			else if (command == "f")
			{
				std::string v1, v2, v3;
				is >> v1 >> v2 >> v3;

				for (const std::string& tokens : { v1, v2, v3 })
				{
					uint32_t index = currentIndex++;
					indices.push_back(index);

					std::vector<std::string> splitTokens = StringTools::Split(tokens, '/');

					size_t posIndex = std::stoull(splitTokens[0]) - 1;
					Vec3f vPosition = positions[posIndex];
					vertices.push_back(vPosition.X);
					vertices.push_back(vPosition.Y);
					vertices.push_back(vPosition.Z);

					if (!splitTokens[1].empty())
					{
						size_t texIndex = std::stoull(splitTokens[1]) - 1;
						Vec2f vTexCoords = texCoords[texIndex];
						vertices.push_back(vTexCoords.X);
						vertices.push_back(vTexCoords.Y);
					}
					else
					{
						vertices.push_back(0);
						vertices.push_back(0);
					}

					size_t normIndex = std::stoull(splitTokens[2]) - 1;
					Vec3f vNormals = normals[normIndex];
					vertices.push_back(vNormals.X);
					vertices.push_back(vNormals.Y);
					vertices.push_back(vNormals.Z);
				}
			}
		}
	}
}