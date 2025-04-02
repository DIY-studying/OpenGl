#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "IndeiceBufer.h"
#include <GL/glew.h>



#define ASSERT(x) if(!(x)) __debugbreak()
#define GLCall(x) GlClearError();\
                x;\
                ASSERT(GlLogCall(#x,__FILE__,__LINE__))

void GlClearError();
bool GlLogCall(const char* function, const char* file, int line);

class Render
{
public:
    Render(){}
    void Draw(const VertexArray& va, const IndeiceBufer& ib, const Shader& shader) const;
    void Clear(unsigned int mask) const;
};