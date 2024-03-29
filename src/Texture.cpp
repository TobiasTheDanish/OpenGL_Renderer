#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GL/glew.h"

#include "Texture.h"
#include "utils/glErrorUtils.h"

Texture::Texture(const std::string& Filepath)
	:m_RendererId(0), m_Filepath(Filepath), m_LocalBuffer(nullptr), 
	m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);

	m_LocalBuffer = stbi_load(Filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4); // 4 for RGBA

	GlCall(glGenTextures(1, &m_RendererId));
	GlCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));

	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));

	GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GlCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::~Texture()
{
	GlCall(glDeleteTextures(1, &m_RendererId));
}

void Texture::Bind(unsigned int slot) const
{
	GlCall(glActiveTexture(GL_TEXTURE0 + slot));
	GlCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));
}

void Texture::UnBind() const
{
	GlCall(glBindTexture(GL_TEXTURE_2D, 0));
}
