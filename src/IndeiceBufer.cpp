#include "IndeiceBufer.h"
#include "GL/glew.h"
#include "Render.h"

IndeiceBufer::IndeiceBufer(const void* data,unsigned int count):m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_RenderID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW));

}
IndeiceBufer::~IndeiceBufer()
{
    GLCall(glDeleteBuffers(1, &m_RenderID));
}

void IndeiceBufer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID));
}
void IndeiceBufer::UnBind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
int IndeiceBufer::GetCount() const
{
    return m_Count;
}
