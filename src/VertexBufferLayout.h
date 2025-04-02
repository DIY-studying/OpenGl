#pragma once

#include<vector>
#include<GL/glew.h>
#include "Render.h"
struct  VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalize;

	inline static unsigned int GetTypeSize(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:							return sizeof(GLfloat);
		case GL_UNSIGNED_INT:				return sizeof(GLuint);
		case GL_UNSIGNED_BYTE:			return sizeof(GLubyte);
		}
		ASSERT(false);
		return -1;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() :m_Stride(0) {}
	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });
		m_Stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
	}
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
		m_Stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT);
	}
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
		m_Stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
	}

	inline const std::vector<VertexBufferElement>& GetElement() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};

