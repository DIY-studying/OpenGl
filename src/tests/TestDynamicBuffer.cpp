#include "TestDynamicBuffer.h"
#include "TestTexture2D.h"
#include "VertexBufferLayout.h"
#include <array>
namespace tests
{
    static std::array<Vertex, 4> CreatQuad(float x,float y,float texID)
    {
        float size = 1.0f;

        Vertex v0;
        v0.position = Vec2{x,y};
        v0.texcoord = Vec2{1.0f,0.0f};
        v0.texID = texID;

        Vertex v1;
        v1.position = Vec2{ x-size,y };
        v1.texcoord = Vec2{ 0.0f,0.0f };
        v1.texID = texID;

        Vertex v2;
        v2.position = Vec2{ x,y +size};
        v2.texcoord = Vec2{ 1.0f,1.0f };
        v2.texID = texID;

        Vertex v3;
        v3.position = Vec2{ x-size,y +size};
        v3.texcoord = Vec2{ 0.0f,1.0f };
        v3.texID = texID;

        return {v0,v1,v2,v3};
    }
    TestDynamicBuffer::TestDynamicBuffer()
        :posA{ 0.5 - 0.5 }, posB{ 0.5 - 0.5 }
    {
        unsigned int indice[] =
        {
            0,1,2,2,1,3,
            4,5,6,6,5,7
        };  

        m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, sizeof(Vertex) * 100,GL_DYNAMIC_DRAW);
        
        m_Shader = std::make_unique<Shader>("res/shader/DynamicBuffer.shader");
        m_IndeiceBufer = std::make_unique<IndeiceBufer>(indice, 12);
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
        float position[] =
        {
            //       vertex             texcoord         texture index
                     0.5f,-0.5f,         1.0f,0.0f,                  0.0f,
                     -0.5f,-0.5f,        0.0f,0.0f,                  0.0f,
                     0.5f, 0.5f,         1.0f,1.0f,                  0.0f,
                      -0.5f,0.5f,        0.0f,1.0f,                  0.0f,

                      0.5f,-0.5f,        1.0f,0.0f,                  1.0f,
                     -0.5f,-0.5f,        0.0f,0.0f,                  1.0f,
                     0.5f, 0.5f,         1.0f,1.0f,                  1.0f,
                     -0.5f,0.5f,         0.0f,1.0f,                  1.0f,
        };
        auto q0 = CreatQuad(posA.x, posA.y, 0.0f);
        auto q1 = CreatQuad(posB.x, posB.y, 1.0f);
        memcpy(position, q0.data(), q0.size()*sizeof(Vertex));
        memcpy(position + q0.size() *5, q1.data(), q1.size() * sizeof(Vertex));
        m_VertexBuffer->Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(position), position);

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
        ImGui::DragFloat2("translation B", &posB.x, 0.1f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    }


}