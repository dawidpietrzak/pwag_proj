#include "CylinderGenerator.h"

#include <GLM/glm.hpp>

void CylinderGenerator::LoadBaseMeshData(const std::string& filePath)
{
	engine::MeshTools::LoadMeshDataFromObjFile(filePath, m_vertices, m_indices);
}

engine::Mesh CylinderGenerator::CreateMesh(float topScale, float bottomScale, float lengthScale = 1)
{
	std::vector<GLfloat> vertices = m_vertices;

	size_t i = 0;
	while (i < vertices.size())
	{
		if (vertices[i + 1] > 0.0f)
		{
			vertices[i] *= topScale;
			vertices[i + 2] *= topScale;
		}
		else
		{
			vertices[i] *= bottomScale;
			vertices[i + 2] *= bottomScale;
		}

        // Scale the y position to add length to the cylinder
        vertices[i + 1] *= lengthScale;
		i += 8;
	}
    
    i = 0;
    while (i < m_indices.size())
    {
        GLuint index1 = m_indices[i];
        GLuint index2 = m_indices[i + 1];
        GLuint index3 = m_indices[i + 2];

        glm::vec3 vertex1(vertices[index1 * 8], vertices[index1 * 8 + 1], vertices[index1 * 8 + 2]);
        glm::vec3 vertex2(vertices[index2 * 8], vertices[index2 * 8 + 1], vertices[index2 * 8 + 2]);
        glm::vec3 vertex3(vertices[index3 * 8], vertices[index3 * 8 + 1], vertices[index3 * 8 + 2]);

        glm::vec3 edge1 = vertex2 - vertex1;
        glm::vec3 edge2 = vertex3 - vertex1;
        glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

        vertices[(size_t)index1 * 8 + 5] = normal.x;
        vertices[(size_t)index1 * 8 + 6] = normal.y;
        vertices[(size_t)index1 * 8 + 7] = normal.z;

        vertices[(size_t)index2 * 8 + 5] = normal.x;
        vertices[(size_t)index2 * 8 + 6] = normal.y;
        vertices[(size_t)index2 * 8 + 7] = normal.z;

        vertices[(size_t)index3 * 8 + 5] = normal.x;
        vertices[(size_t)index3 * 8 + 6] = normal.y;
        vertices[(size_t)index3 * 8 + 7] = normal.z;

        i += 3;
    }

	return engine::MeshTools::CreateMeshFromRawData(vertices, m_indices);
}