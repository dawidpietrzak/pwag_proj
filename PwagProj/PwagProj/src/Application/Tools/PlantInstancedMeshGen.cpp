#include "PlantInstancedMeshGen.h"

#include <Engine/Tools/MeshTools.h>

#include <glm/gtc/type_ptr.hpp>

void PlantInstancedMeshGen::LoadBaseMeshData(const std::string& filePath)
{
	engine::MeshTools::LoadMeshDataFromObjFile(filePath, m_vertices, m_indices);
}

engine::Mesh PlantInstancedMeshGen::GenerateMesh(const std::vector<PlantSegment>& plantSegments) const
{
	engine::VertexAttrib vertexAttrib;
	vertexAttrib.Create({
		{ 0, 3 },	// Position 3d
		{ 1, 2 },	// TexCoord 2d
		{ 2, 3 },	// Normal 3d
	});

	engine::VertexBuffer commonVertexBuffer;
	commonVertexBuffer.Create(m_vertices, vertexAttrib);

	engine::IndexBuffer indexBuffer;
	indexBuffer.Create(m_indices);

	size_t allocSize = plantSegments.size() * sizeof(PlantSegment) / sizeof(float);
	std::vector<GLfloat> perInstanceBufferData;
	perInstanceBufferData.reserve(allocSize);

	for (const PlantSegment& plantSegment : plantSegments)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				perInstanceBufferData.push_back(plantSegment.Transform[i][j]);

		perInstanceBufferData.push_back(plantSegment.TopScale);
		perInstanceBufferData.push_back(plantSegment.BottomScale);
		perInstanceBufferData.push_back(plantSegment.Length);
	}

	engine::VertexAttrib perInstanceAttrib;
	perInstanceAttrib.Create({
		{ 3, 4, 1 },	// Vec4 Transform Column 1 per instance
		{ 4, 4, 1 },	// Vec4 Transform Column 2 per instance
		{ 5, 4, 1 },	// Vec4 Transform Column 3 per instance
		{ 6, 4, 1 },	// Vec4 Transform Column 4 per instance
		{ 7, 1, 1 },	// TopScale per instance
		{ 8, 1, 1 },	// BottomScale per instance
		{ 9, 1, 1 },	// Length per instance
	});
	engine::VertexBuffer perInstanceBuffer;
	perInstanceBuffer.Create(perInstanceBufferData, perInstanceAttrib);
	
	engine::Mesh mesh;
	mesh.CreateInstanced({ commonVertexBuffer, perInstanceBuffer }, indexBuffer, (GLuint)plantSegments.size());
	return mesh;
}