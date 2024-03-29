#include "GL/glew.h"
#include "VertexBuffer.h"
#include "utils/glErrorUtils.h"
#include <exception>

VertexBuffer::VertexBuffer() 
{
	GlCall(glGenBuffers(1, &m_RendererId));
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GlCall(glGenBuffers(1, &m_RendererId));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
	GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GlCall(glDeleteBuffers(1, &m_RendererId));
}

void VertexBuffer::Bind() const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void VertexBuffer::UnBind() const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::SetBuffer(const void *data, unsigned int size)
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
	GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
