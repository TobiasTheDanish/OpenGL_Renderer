#pragma once

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

class RenderExample2D {
private:
	VertexArray m_va;
	VertexBuffer m_vb;
	IndexBuffer m_ib;
	Shader m_Shader;
	Texture m_Texture;

public:
	RenderExample2D(const std::string& Filepath);
	~RenderExample2D();

	void Run(Renderer& renderer) const;
};
