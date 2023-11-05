#include "AssetManager.h"

#include <Engine/Tools/MeshTools.h>

namespace engine
{
	void AssetManager::Destroy()
	{
		for (auto& texture : m_textures)
			texture.second.Destroy();

		for (auto& mesh : m_meshes)
			mesh.second.Destroy();
	}

	Material& AssetManager::CreateMaterial(const std::string& shaderName, const std::string& materialName)
	{
		Shader shader = m_shaders.at(shaderName);
		Material material(shader);
		m_materials[materialName] = material;
		return m_materials[materialName];
	}

	Texture AssetManager::LoadTextureFromFile(const std::string& filePath, const std::string& textureName)
	{
		Image image = ImageTools::LoadImageFromFile(filePath);
		Texture texture;
		texture.Create(image);
		m_textures[textureName] = texture;
		return texture;
	}

	Mesh AssetManager::LoadMeshFromFile(const std::string& filePath, const std::string& meshName)
	{
		Mesh mesh = MeshTools::LoadMeshFromObjFile(filePath);
		m_meshes[meshName] = mesh;
		return mesh;
	}
}
