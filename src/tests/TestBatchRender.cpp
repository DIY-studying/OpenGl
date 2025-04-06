#include "TestBatchRender.h"
#include "TestTexture2D.h"
#include "VertexBufferLayout.h"
namespace tests
{
    TestBatchRender::TestBatchRender()
        :m_Proj(glm::ortho(-2.0f, 2.0f, -2.0f, 1.5f, -2.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
        m_TranslationA(0), m_TranslationB(1, 0, 0)
    {
        float position[] =
        {
        //       vertex             texcoord     translate index    texture index
                 0.5f,-0.5f,         1.0f,0.0f,              0.0f,                      0.0f,
                 -0.5f,-0.5f,        0.0f,0.0f,              0.0f,                      0.0f,
                 0.5f, 0.5f,         1.0f,1.0f,              0.0f,                      0.0f,
                  -0.5f,0.5f,        0.0f,1.0f,              0.0f,                      0.0f,

                  0.5f,-0.5f,        1.0f,0.0f,              1.0f,                      1.0f,
                 -0.5f,-0.5f,        0.0f,0.0f,              1.0f,                      1.0f,
                 0.5f, 0.5f,         1.0f,1.0f,              1.0f,                      1.0f,
                 -0.5f,0.5f,         0.0f,1.0f,              1.0f,                      1.0f,
        };
        unsigned int indice[] =
        {
            0,1,2,
            2,1,3,
            4,5,6,
            6,5,7
        };
        m_Shader = std::make_unique<Shader>("res/shader/BatchRender.shader");
        m_VertexBuffer = std::make_unique<VertexBuffer>(position, 8 * 6 * sizeof(float));
        m_IndeiceBufer = std::make_unique<IndeiceBufer>(indice, 12);
        m_VertexArray = std::make_unique<VertexArray>();
        m_TextureA = std::make_unique<Texture>("res/texture/awesomeface.png");
        m_TextureB = std::make_unique<Texture>("res/texture/OIP-C.jpg");

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        layout.Push<float>(1);
        layout.Push<float>(1);

        m_VertexArray->AddBuffeer(*m_VertexBuffer, layout);
    }



    void TestBatchRender::OnUpdate(float deltatime)
    {

    }
    void TestBatchRender::OnRender()
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
            int sample[] = {0,1};
            m_Shader->SetUniformi1iv("ourTexture", 2,sample);
            glm::mat4 modelA = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 modelB= glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvpA = m_Proj * m_View * modelA;
            glm::mat4 mvpB= m_Proj * m_View * modelB;

            m_Shader->SetUniformMat4fv("u_MVP[0]", mvpA);
            m_Shader->SetUniformMat4fv("u_MVP[1]", mvpB);

            render.Draw(*m_VertexArray, *m_IndeiceBufer, *m_Shader);
        }
       
    }
    void TestBatchRender::OnImGuiRender()
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SliderFloat3("translation A", &m_TranslationA.x, -2.0f, 2.0f);
        ImGui::SliderFloat3("translation B", &m_TranslationB.x, -2.0f, 2.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    }


}
