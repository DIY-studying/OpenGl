#include "Texture.h"
#include "vendor/stb_image/stb_image.h"
#include "Render.h"
#include <iostream>


Texture::Texture(std::string filePath)
	:m_RenderID(0),m_filePath(filePath),m_LocalBuffer(nullptr),
	m_Width(0),m_Height(0),m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	if (m_LocalBuffer)
	{

		GLCall(glGenTextures(1, &m_RenderID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));

		stbi_image_free(m_LocalBuffer);
	}

	GLCall(glBindTexture(GL_TEXTURE_2D,0));
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1,&m_RenderID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0+slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));
}

void Texture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}