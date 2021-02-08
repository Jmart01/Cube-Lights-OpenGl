#pragma once
#include <string>
class shader
{
public:
	shader(const std::string& SrcDir, unsigned int Type);
	unsigned int GetShaderID() const
	{
		return m_shaderID;
	}
private:
	std::string GetSourcString(const std::string& Dir);


private:
	unsigned int m_shaderID;
};

