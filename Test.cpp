
#include "GL/glew.h"
#define GLFW_DLL
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <iostream>
static void GlCheckError()
{
    while (GLenum error = glGetError())
    {
        std::cout << "[ OpenGl Error] Code:" << error << std::endl;
    }
}
int Main()
{


    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(460, 480, "Hello !", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glewExperimental = GL_TRUE;
    glfwMakeContextCurrent(window);

    GLenum ret = glewInit();
    if (GLEW_OK != ret)
    {
        // Problem: glewInit failed, something is seriously wrong.
        fprintf(stderr, "Error: %s\n", glewGetErrorString(ret));
        return 1;
    }

 
    // Two triangles:
    float triangle_vertices[] = {
        0.5f,-0.5f,
       -0.5f,-0.5f,
        0.5f, 0.5f,
        -0.5f,0.5f,
       -0.5f,-0.5f,
        0.5f,0.5f,
    };
    unsigned int indice[6] =
    {
        0,1,2,
    };
    GLuint vertex_buffer_object = 0; // VBO
    glGenBuffers(1, &vertex_buffer_object);
    {
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

        //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3, triangle_vertices, GL_STATIC_DRAW);
        // The previous command was for drawing a triangle, while the following one is intended for 
        // drawing a square, although it doesn't yet work !
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2* 6, triangle_vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind
    }


    unsigned int ibo;
    glGenBuffers(1, &ibo);
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), indice, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }


    GLuint vertex_array_object = 0;
    glGenVertexArrays(1, &vertex_array_object);
    {
        glBindVertexArray(vertex_array_object);

        glEnableVertexAttribArray(0); // enable the first input variable (vertex position)
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    
    GLuint shader_program_object = 0;
    { // SHADERS

        const char* vertex_shader_str =
            "#version 410\n"
            "in vec3 a_position;\n"
            "void main() {\n"
            "gl_Position = vec4(a_position, 1.0);\n"
            "}";

        const char* fragment_shader_str =
            "#version 410\n"
            "out vec4 o_frag_colour;\n"
            "void main() {\n"
            "o_frag_colour = vec4(0.5, 0.0, 0.5, 1.0);\n"
            "}\n";

        GLuint vertex_shader_object = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader_object, 1, &vertex_shader_str, NULL);
        glCompileShader(vertex_shader_object);

        GLuint fragment_shader_object = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader_object, 1, &fragment_shader_str, NULL);
        glCompileShader(fragment_shader_object);

        shader_program_object = glCreateProgram();
        glBindAttribLocation(shader_program_object, 0, "a_position");

        glAttachShader(shader_program_object, vertex_shader_object);
        glAttachShader(shader_program_object, fragment_shader_object);
        glLinkProgram(shader_program_object);

    }

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader_program_object);
        {
            glBindVertexArray(vertex_array_object);
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
                //glDrawArrays(GL_TRIANGLES, 0, 3);
                //glDrawArrays(GL_TRIANGLES, 0, 6);
                glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT,nullptr);
            }
            glBindVertexArray(0);
        }
        glUseProgram(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    GlCheckError();
    glfwTerminate();
    return 0;
}

