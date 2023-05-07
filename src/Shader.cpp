#include "GL/glew.h"
#include "Shader.h"
#include "utils/shaderUtils.h"
#include "utils/glErrorUtils.h"
#include <iostream>
#include <unordered_map>

Shader::Shader(const std::string& filepath)
	: filepath(filepath),
	  m_RendererId(0)
{
	m_RendererId = ShaderUtil::SetupShader(filepath);
	Bind();
}

Shader::~Shader()
{
	GlCall(glDeleteProgram(m_RendererId));
}

void Shader::Bind() const
{
	GlCall(glUseProgram(m_RendererId));
}

void Shader::UnBind() const
{
	GlCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& uniformName, int value)
{
	GlCall(glUniform1i(GetUniformLocation(uniformName), value));
}

void Shader::SetUniform1f(const std::string& uniformName, float value)
{
	GlCall(glUniform1f(GetUniformLocation(uniformName), value));
}

void Shader::SetUniform4f(const std::string &uniformName, float v1, float v2, float v3, float v4)
{
	GlCall(glUniform4f(GetUniformLocation(uniformName), v1, v2, v3, v4));
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
		std::cout << "[WARNING]: Uniform named: '" << uniformName << "' doesn't exist or isn't in use, but is attempted to be set!" << std::endl;
	}

	m_UniformCache[uniformName] = location;
	return location;
}
