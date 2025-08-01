#pragma once
#include "VertexBuffer.h"

class VertexBufferLayout;
class VertexArray
{
private:
	unsigned int m_RenderID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffeer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};

