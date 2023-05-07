#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererId;
	unsigned int m_Count = 0;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void UnBind() const;
	void SetData(const unsigned int* data);
	void SetCount(unsigned int count);
	unsigned int GetCount() const;
};
