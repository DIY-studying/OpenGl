#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include<sstream>
#include <fstream>
#include "stb_image/stb_image.h"

#include "Render.h"
#include "VertexBuffer.h"
#include "IndeiceBufer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include "imgui/imgui_impl_glfw.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "Hazel Eigen", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    glfwSwapInterval(1);

    // Must down to window's context
    if (glewInit() != GLEW_OK)
        std::cout << "error." << std::endl;

   std::cout << glGetString(GL_VERSION) << std::endl;
   //-----------------------------------------------------------------------------------------
   {
       float triangle_vertices[] = {
          0,0.5f,
         -0.5f,0.0f,
          0.5f,0.0f,
         -0.5f,0.0f,
          0.5f,0.0f,
          0,-0.5f,
       };
       VertexBuffer vb1(triangle_vertices, 6 * 2 * sizeof(float));
       
       tests::Test* currentTest=nullptr;
       tests::TestMenu* testMenu = new tests::TestMenu(currentTest);
       testMenu->RegisterTest<tests::TestClearColor>("Clear tests");
       testMenu->RegisterTest<tests::TestTexture2D>("2D Texture");
       currentTest = testMenu;
       
      
       Render render;

       // Setup Dear ImGui context
       ImGui::CreateContext();

       // Setup Platform/Renderer backends
       ImGui_ImplGlfw_InitForOpenGL(window, true);
       ImGui_ImplOpenGL3_Init(glsl_version);
       ImGui::StyleColorsDark();

       /* Loop until the user closes the window */
       while (!glfwWindowShouldClose(window))
       {
           /* Render here */
           glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
           render.Clear(GL_COLOR_BUFFER_BIT);

           // Start the Dear ImGui frame
           ImGui_ImplOpenGL3_NewFrame();
           ImGui_ImplGlfw_NewFrame();
           ImGui::NewFrame();
           
           currentTest->OnUpdate(0);
           currentTest->OnRender();
           
           ImGui::Begin("Test");
           if (currentTest != testMenu && ImGui::Button("< -"))
           {
               delete currentTest;
               currentTest=testMenu;
           }
           currentTest->OnImGuiRender();
           ImGui::End();

           // Rendering
           ImGui::Render();
           int display_w, display_h;
           glfwGetFramebufferSize(window, &display_w, &display_h);
           glViewport(0, 0, display_w, display_h);
           ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

           /* Swap front and back buffers */
           glfwSwapBuffers(window);
           glfwPollEvents();
       }
       
   }
   // 用花括号括住是为了里面的类调用析构函数
   // 在glfwTerminate之前释放资源（调用），如果不这样做
   // 会破坏环境报错。这背后的原理可能是因为重复释放资源，这是未定义的
   // 可以手动释放资源。
   // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}