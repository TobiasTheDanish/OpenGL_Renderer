#pragma once
#include "utils/glErrorUtils.h"

class VertexBuffer 
{
private:
	unsigned int m_RendererId;

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind();
	void UnBind();
};
