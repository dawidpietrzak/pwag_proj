#include "ShaderCompiler.h"

#include <Engine/Tools/FileTools.h>
#include <cstdint>
#include <sstream>

namespace engine
{
	enum class LoadShaderType : uint8_t
	{
		Vertex,
		Fragment,
	};

	Shader ShaderCompiler::CompileFromFile(const std::string& fileName)
	{
		std::string vertexShaderCode;
		std::string fragmentShaderCode;
		ParseFile(fileName, vertexShaderCode, fragmentShaderCode);

		char const* cStrVertexSource = vertexShaderCode.c_str();
		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &cStrVertexSource, NULL);
		glCompileShader(vertexShaderId);

		GLint result;
		GLint infoLength;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
		glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLength);
		if (infoLength > 0)
		{
			std::vector<char> errMsg(infoLength + 1);
			glGetShaderInfoLog(vertexShaderId, infoLength, NULL, &errMsg[0]);
			std::string msgContent(errMsg.begin(), errMsg.end());
			throw std::exception(msgContent.c_str());
		}

		char const* cStrFragmentSource = fragmentShaderCode.c_str();
		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderId, 1, &cStrFragmentSource, NULL);
		glCompileShader(fragmentShaderId);

		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
		glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLength);
		if (infoLength > 0)
		{
			std::vector<char> errMsg(infoLength + 1);
			glGetShaderInfoLog(fragmentShaderId, infoLength, NULL, &errMsg[0]);
			std::string msgContent(errMsg.begin(), errMsg.end());
			throw std::exception(msgContent.c_str());
		}

		GLuint shaderProgramId = glCreateProgram();
		glAttachShader(shaderProgramId, vertexShaderId);
		glAttachShader(shaderProgramId, fragmentShaderId);

		glLinkProgram(shaderProgramId);
		
		glDetachShader(shaderProgramId, vertexShaderId);
		glDetachShader(shaderProgramId, fragmentShaderId);
		return Shader(shaderProgramId);
	}

	void ShaderCompiler::ParseFile(const std::string& fileName, std::string& vertexShaderCode, std::string& fragmentShaderCode)
	{
		std::vector<std::string> lines = FileTools::ReadAllLines(fileName);
		LoadShaderType loadShaderType = LoadShaderType::Vertex;

		std::stringstream vertexStream;
		std::stringstream fragmentStream;

		for (const std::string& line : lines)
		{
			char firstChar = line.size() > 0 ? line[0] : 0;
			if (firstChar == '[' && line == "[engine::fragment_part]")
			{
				loadShaderType = LoadShaderType::Fragment;
			}
			else if (firstChar == '[' && line == "[engine::vertex_part]")
			{
				loadShaderType = LoadShaderType::Vertex;
			}
			else
			{
				if (loadShaderType == LoadShaderType::Vertex)
				{
					vertexStream << line << "\n";
				}
				else
				{
					fragmentStream << line << "\n";
				}
			}
		}

		vertexShaderCode = vertexStream.str();
		fragmentShaderCode = fragmentStream.str();
	}
}