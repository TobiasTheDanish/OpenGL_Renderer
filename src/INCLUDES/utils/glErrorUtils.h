#pragma once
#include <GL/glew.h>
#include <iostream>

#define ASSERT(x) if ((x)) std::terminate;
#define GlCall(x) GlClearError(); x; ASSERT(GlLogMessage(#x, __FILE__, __LINE__))

void GlClearError();

const char* GlConvertErrorCode(unsigned int error);

bool GlLogMessage(const char* function, const char* file, int line);
