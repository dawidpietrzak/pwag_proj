#pragma once

#include <Engine/Rendering/OpenGL/Shader.h>
#include <string>

namespace engine
{
	class ShaderCompiler
	{
	public:
		static Shader CompileFromFile(const std::string& fileName);

	private:
		static void ParseFile(const std::string& fileName, std::string& vertexShaderCode, std::string& fragmentShaderCode);
	};
}