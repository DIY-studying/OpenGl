#include "VertexBuffer.h"
#include "GL/glew.h"
#include "Render.h"


VertexBuffer::VertexBuffer(const void* data,unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RenderID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
VertexBuffer::VertexBuffer(const void* data, unsigned int size,unsigned int usage)
{
    GLCall(glGenBuffers(1, &m_RenderID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data,usage));
}
VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RenderID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
}
void VertexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
}