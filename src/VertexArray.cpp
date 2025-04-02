#include "VertexArray.h"
#include "Render.h"
#include"VertexBufferLayout.h"


VertexArray::VertexArray()
{
	GLCall( glGenVertexArrays(1, &m_RenderID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1,&m_RenderID));
}

void VertexArray::AddBuffeer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	vb.Bind();
	Bind();
	const auto& elements = layout.GetElement();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalize, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetTypeSize(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RenderID));
}

void VertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}
