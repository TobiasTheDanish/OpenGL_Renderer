#include "IndexBuffer.h"
#include "utils/glErrorUtils.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
{
	m_Count = count;

	GlCall(glGenBuffers(1, &m_RendererId));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
	GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GlCall(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::Bind()
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::UnBind()
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
