#include "utils/glErrorUtils.h"

#define ASSERT(x) if ((x)) std::terminate;
#define GlCall(x) GlClearError(); x; ASSERT(GlLogMessage(#x, __FILE__, __LINE__))

void GlClearError()
{
	while (glGetError() != 0);
}

const char* GlConvertErrorCode(unsigned int error)
{
	/*
#define GL_INVALID_ENUM 0x0500
#define GL_INVALID_VALUE 0x0501
#define GL_INVALID_OPERATION 0x0502
#define GL_STACK_OVERFLOW 0x0503
#define GL_STACK_UNDERFLOW 0x0504
#define GL_OUT_OF_MEMORY 0x0505
#define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
	 */
	if (error == 1280) 
	{
		return "GL_INVALID_ENUM";
	}
	else if (error == 1281)
	{
		return "GL_INVALID_VALUE";
	}
	else if (error == 1282)
	{
		return "GL_INVALID_OPERATION";
	}
	else if (error == 1283)
	{
		return "GL_STACK_OVERFLOW";
	}
	else if (error == 1284)
	{
		return "GL_STACK_UNDERFLOW";
	}
	else if (error == 1285)
	{
		return "GL_OUT_OF_MEMORY";
	}
	else if (error == 1286)
	{
		return "GL_INVALID_FRAMEBUFFER_OPERATION";
	}
	else 
	{
		return "UNKNOWN ERROR CODE";
	}
}

bool GlLogMessage(const char* function, const char* file, int line)
{
	bool errorFound = false;

	while (unsigned int error = glGetError()) {
		std::cout << "\n----------------------------       [OPENGL ERROR]       ----------------------------\n"
			<< "---   (ERRORCODE: " << error << ") - " << GlConvertErrorCode(error) << " from: " << function <<"\n"
			<< "---   IN "<< file << " ON line:" << line << "\n" << std::endl;
		errorFound = true;
	}

	return errorFound;
}
