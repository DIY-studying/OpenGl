#include "TestDynamicBuffer.h"
#include "TestTexture2D.h"
#include "VertexBufferLayout.h"
#include <iostream>
namespace tests
{
    static Vertex* CreatQuad(Vertex* target,float x,float y,float texID)
    {
        float size = 0.08f;

        target->position = {x,y};
        target->texcoord = {0.0f,0.0f};
        target->texID = texID;
        target++;

        target->position = { x+size,y };
        target->texcoord = { 1.0f,0.0f };
        target->texID = texID;
        target++;

        target->position = { x + size,y +size};
        target->texcoord = { 1.0f,1.0f };
        target->texID = texID;
        target++;

        target->position = { x,y +size};
        target->texcoord = { 0.0f,1.0f };
        target->texID = texID;
        target++;

        return target;
    }
    TestDynamicBuffer::TestDynamicBuffer()
        :posA{ 0, 0 }, posB{ 0.5 ,- 0.5 },m_IndeiceBufer(nullptr)
    {
        
        m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex) * MaxQuadCount*4, GL_DYNAMIC_DRAW);
        m_IndeiceBufer = std::make_unique<IndeiceBufer>(nullptr, MaxQuadCount * 6, GL_DYNAMIC_DRAW);


        m_Shader = std::make_unique<Shader>("res/shader/DynamicBuffer.shader");
        m_VertexArray = std::make_unique<VertexArray>();
        m_TextureA = std::make_unique<Texture>("res/texture/awesomeface.png");
        m_TextureB = std::make_unique<Texture>("res/texture/OIP-C.jpg");

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        layout.Push<float>(1);

        m_VertexArray->AddBuffeer(*m_VertexBuffer, layout);

    }



    void TestDynamicBuffer::OnUpdate(float deltatime)
    {
        unsigned int indice[MaxQuadCount * 6];
        unsigned int offset = 0;
        for (int i = 0; i < MaxQuadCount * 6; i += 6)
        {
            indice[0 + i] = 0 + offset;
            indice[1 + i] = 1 + offset;
            indice[2 + i] = 2 + offset;

            indice[3 + i] = 2 + offset;
            indice[4 + i] = 3 + offset;
            indice[5 + i] = 0 + offset;

            offset += 4;
        }
        
        std::array<Vertex,50> vertexs;
        Vertex* buffer = vertexs.data();
        unsigned int indexCount = 0;
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                buffer = CreatQuad(buffer, x/5.0f+0.1f, y/5.0f+ 0.1f, (x + y) % 2);
                indexCount++;
            }
        }
        buffer = CreatQuad(buffer, posA.x, posA.y, 0.0f);
        indexCount++;

        // https://gamedev.stackexchange.com/questions/187972/how-to-update-indices-for-dynamic-mesh-in-opengl
        // 对dynamic indeice buffer 的改进，chenor 偷懒了，这B天天偷懒，害的我要动脑子。
        m_IndeiceBufer->Bind();
        void* vbo = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
        memcpy(vbo, indice, indexCount*6*sizeof(unsigned int));
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);


        m_VertexBuffer->Bind();
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, vertexs.size() * sizeof(Vertex), vertexs.data()));

    }
    void TestDynamicBuffer::OnRender()
    {
        GLCall(glClearColor(0, 0, 0, 1));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE));

        Render render;
        m_Shader->Bind();
        {
            m_TextureA->Bind(0);
            m_TextureB->Bind(1);
            int sample[] = { 0,1 };
            m_Shader->SetUniformi1iv("ourTexture", 2, sample);

            render.Draw(*m_VertexArray, *m_IndeiceBufer, *m_Shader);
        }

    }
    void TestDynamicBuffer::OnImGuiRender()
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::DragFloat2("translation A", &posA.x,0.1f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    }


}