#pragma once

#include <string>
struct ShaderSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class ShaderUtil {
public:
	static ShaderSource parseShader(const std::string& filePath);

	static unsigned int CompileShader(const unsigned int type, const std::string& source);

	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	static unsigned int SetupShader(const std::string& filePath);
};
