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
		texture.CreateFromImage(image);
		m_textures[textureName] = texture;
		return texture;
	}

	Texture AssetManager::LoadCubeMapFromFiles(const std::vector<std::string>& filePaths, const std::string& textureName)
	{
		std::vector<Image> images;
		images.reserve(6);

		for (const std::string& filePath : filePaths)
		{
			Image image = ImageTools::LoadImageFromFile(filePath);
			images.push_back(image);
		}

		Texture texture;
		texture.CreateCubeMap(images);
		m_textures[textureName] = texture;
		return texture;
	}

	void AssetManager::LoadMesh(Mesh mesh, const std::string& meshName)
	{
		m_meshes[meshName] = mesh;
	}

	Mesh AssetManager::LoadMeshFromFile(const std::string& filePath, const std::string& meshName)
	{
		Mesh mesh = MeshTools::LoadMeshFromObjFile(filePath);
		m_meshes[meshName] = mesh;
		return mesh;
	}
}
