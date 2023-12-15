#pragma once

#include <unordered_map>
#include <string>

#include <Engine/Rendering/Material.h>
#include <Engine/Rendering/Mesh.h>
#include <Engine/Rendering/OpenGL/Texture.h>

namespace engine
{
	class AssetManager
	{
	public:
		AssetManager(const std::unordered_map<std::string, Shader>& shaders) : m_shaders(shaders) {}
		void Destroy();

		Material& CreateMaterial(const std::string& shaderName, const std::string& materialName);
		Material GetMaterial(const std::string& materialName) const { return m_materials.at(materialName); }

		Texture LoadCubeMapFromFiles(const std::vector<std::string>& filePaths, const std::string& textureName);
		Texture LoadTextureFromFile(const std::string& filePath, const std::string& textureName);
		Texture GetTexture(const std::string& textureName) { return m_textures.at(textureName); }

		void LoadMesh(Mesh mesh, const std::string& meshName);
		Mesh LoadMeshFromFile(const std::string& filePath, const std::string& meshName);
		Mesh GetMesh(const std::string& meshName) const { return m_meshes.at(meshName); }

	private:
		std::unordered_map<std::string, Material> m_materials;
		std::unordered_map<std::string, Mesh> m_meshes;
		std::unordered_map<std::string, Texture> m_textures;

		const std::unordered_map<std::string, Shader>& m_shaders;
	};
}



