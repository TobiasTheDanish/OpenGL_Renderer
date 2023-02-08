#pragma once

#include <string>
#include <unordered_map>

class Shader 
{
private:
	std::string filepath;
	unsigned int m_RendererId;
	std::unordered_map<std::string, int> m_UniformCache;

public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind();
	void UnBind();
	void SetUniform(const std::string& uniformName, float v1, float v2, float v3, float v4);

private:
	int GetUniformLocation(const std::string& uniformName);
};
