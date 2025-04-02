#include"Render.h"
#include<iostream>


void GlClearError()
{
    while (glGetError() != GL_NO_ERROR);
}
bool GlLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[ OpenGl Error] Code:" << error << " Function: " << function
            << " File: " << file << " Line: " << line << std::endl;
        return false;
    }
    return true;
}

void Render::Draw(const VertexArray& va, const IndeiceBufer& ib, const Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
void Render::Clear(unsigned int mask) const
{
    glClear(mask);
}