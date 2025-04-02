#include "TestTexture2D.h"
#include "VertexBufferLayout.h"

namespace tests
{
    TestTexture2D::TestTexture2D()
        :m_Proj(glm::ortho(-2.0f, 2.0f, -2.0f, 1.5f,-2.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
        m_TranslationA(0), m_TranslationB(1, 0, 0)
    {
        float position[] =
        {
                 0.5f,-0.5f,         1.0f,0.0f,
                 -0.5f,-0.5f,        0.0f,0.0f,
                 0.5f, 0.5f,         1.0f,1.0f,
                  -0.5f,0.5f,        0.0f,1.0f
        };
        unsigned int indice[6] =
        {
            0,1,2,
            2,1,3
        };
        m_Shader = std::make_unique<Shader>("res/shader/Basic.shader");
        m_VertexBuffer = std::make_unique<VertexBuffer>(position, 4 * 4 * sizeof(float));
        m_IndeiceBufer = std::make_unique<IndeiceBufer>(indice, 6);
        m_VertexArray = std::make_unique<VertexArray>();
        m_Texture = std::make_unique<Texture>("res/texture/awesomeface.png");

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        m_VertexArray->AddBuffeer(*m_VertexBuffer, layout);
    }



    void TestTexture2D::OnUpdate(float deltatime)
    {

    }
    void TestTexture2D::OnRender()
    {
        GLCall(glClearColor(0,0,0,1));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE));

        Render render;
        m_Shader->Bind();
        {
            m_Texture->Bind(0);
            m_Shader->SetUniformi1("ourTexture", 0);
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->SetUniformMatf4("u_MVP", mvp);
            render.Draw(*m_VertexArray, *m_IndeiceBufer, *m_Shader);
        }
        {
            m_Texture->Bind(0);
            m_Shader->SetUniformi1("ourTexture", 0);
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->SetUniformMatf4("u_MVP", mvp);
            render.Draw(*m_VertexArray, *m_IndeiceBufer, *m_Shader);
        }
    }
    void TestTexture2D::OnImGuiRender()
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SliderFloat3("translation A", &m_TranslationA.x, -2.0f, 2.0f);
        ImGui::SliderFloat3("translation B", &m_TranslationB.x, -2.0f, 2.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    }
}