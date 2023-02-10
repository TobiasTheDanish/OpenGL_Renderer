#include "GL/glew.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "utils/glErrorUtils.h"

VertexArray::VertexArray()
{
	GlCall(glGenVertexArrays(1, &m_RendererId));
}

VertexArray::~VertexArray()
{
	GlCall(glDeleteVertexArrays(1, &m_RendererId));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	const std::vector<VertexBufferElement>& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const VertexBufferElement& element = elements[i];
		unsigned char offset = 0;
		GlCall(glEnableVertexAttribArray(i));
		GlCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, 
				layout.GetStride(), (const void*)  offset));
		offset += element.count * element.GetSizeOfType(element.type);
	}

}

void VertexArray::Bind() const
{
	GlCall(glBindVertexArray(m_RendererId));
}

void VertexArray::UnBind() const
{
	GlCall(glBindVertexArray(0));
}
