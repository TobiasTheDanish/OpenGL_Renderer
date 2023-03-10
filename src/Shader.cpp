#include "utils/glErrorUtils.h"
#include "Shader.h"
#include "utils/shaderUtils.h"
#include <unordered_map>

Shader::Shader(const std::string& filepath)
	: filepath(filepath),
	  m_RendererId(0)
{
	m_RendererId = ShaderUtil::SetupShader(filepath);
	GlCall(glUseProgram(m_RendererId));
}

Shader::~Shader()
{
	GlCall(glDeleteProgram(m_RendererId));
}

void Shader::Bind()
{
	GlCall(glUseProgram(m_RendererId));
}

void Shader::UnBind()
{
	GlCall(glUseProgram(0));
}

void Shader::SetUniform(const std::string &uniformName, float v1, float v2, float v3, float v4)
{
	GlCall(glUniform4f(GetUniformLocation(uniformName), v1, v2, v3, v4))
}

int Shader::GetUniformLocation(const std::string& uniformName)
{
	if (m_UniformCache.find(uniformName) != m_UniformCache.end())
	{
		return m_UniformCache[uniformName];
	}

	GlCall(int location = glGetUniformLocation(m_RendererId, uniformName.c_str()));

	if (location == -1)
	{
		std::cout << "[WARNING]: Uniform named: '" << uniformName << "' doesn't exist!" << std::endl;
	}

	m_UniformCache[uniformName] = location;
	return location;
}
