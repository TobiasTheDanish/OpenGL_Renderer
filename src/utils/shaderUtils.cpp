#include "utils/glErrorUtils.h"
#include "utils/shaderUtils.h"

#include <GL/glew.h>

#include <iostream>
#include <sstream>
#include <fstream>

ShaderSource ShaderUtil::parseShader(const std::string& filePath) 
{
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::ifstream fileStream(filePath);
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;

	std::string line;
	while(getline(fileStream, line))
	{
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) 
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) 
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int ShaderUtil::CompileShader(const unsigned int type, const std::string& source) 
{
	const unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	GlCall(glShaderSource(shader, 1, &src, NULL));
	GlCall(glCompileShader(shader));

	int shaderCompiled;
	GlCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled));

	if (!shaderCompiled) {
		int infoLogLength;
		GlCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength));
		char* infoLog;
		GlCall(glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog));

		std::string typeStr = type == GL_FRAGMENT_SHADER? "Fragment" : "VERTEX";
		std::cout << "[ERROR] " << typeStr << "shader of type " << " didnt compile" << std::endl;
		std::cout << "[ERROR] " << infoLog << std::endl;
		GlCall(glDeleteShader(shader));
		return 0;
	}

	return shader;
}

unsigned int ShaderUtil::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) 
{
	const unsigned int program = glCreateProgram();
	const unsigned int vShader = CompileShader(GL_VERTEX_SHADER, vertexShader);
	const unsigned int fShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GlCall(glAttachShader(program, vShader));
	GlCall(glAttachShader(program, fShader));
	GlCall(glLinkProgram(program));
	
	int programLinked;
	GlCall(glGetProgramiv(program, GL_LINK_STATUS, &programLinked));
	if (!programLinked) {
		GlCall(glDeleteProgram(program));
		return 0;
	}
	GlCall(glDeleteShader(vShader));
	GlCall(glDeleteShader(fShader));

	return program;
}

unsigned int ShaderUtil::SetupShader(const std::string& filePath)
{
	ShaderSource shaderSrc = parseShader("../res/shaders/basic.shader");

	return CreateShader(shaderSrc.vertexSource, shaderSrc.fragmentSource);
}
