#include "shader.h"
#include <glad/glad.h>
#include <fstream>

shader::shader(const std::string& SrcDir, unsigned int Type)
	:m_shaderID(glCreateShader(Type))
{
	std::string VertexShaderSrcStr = GetSourcString(SrcDir);
	const char* VertexSorcRaw = VertexShaderSrcStr.c_str();
	glShaderSource(m_shaderID, 1, &VertexSorcRaw, nullptr);
	glCompileShader(m_shaderID);
}

std::string shader::GetSourcString(const std::string& Dir)
{
	std::ifstream ShaderIF{ Dir };
	std::string ShaderSrcString;
	std::string Read;
	while (std::getline(ShaderIF, Read))
	{
		ShaderSrcString += Read;
		ShaderSrcString += '\n';
	}

	return ShaderSrcString;
}
