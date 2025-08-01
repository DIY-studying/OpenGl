#pragma once


class VertexBuffer
{
private:
	unsigned int m_RenderID;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(const void* data, unsigned int size, unsigned int usage);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};

