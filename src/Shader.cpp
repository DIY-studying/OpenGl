#include "Shader.h"
#include<GL/glew.h>

#include <iostream>
#include<sstream>
#include <fstream>

#include "Render.h"

ShaderProgramSource Shader::PharseShader(const std::string& path)
{
    std::ifstream stream(path);
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::stringstream ss[2];

    std::string line;
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            if (ShaderType::NONE != type)
                ss[(int)type] << line << "\n";
        }
    }
    return { ss[0].str(),ss[1].str() };
}

Shader::Shader(const std::string& filePath)
    :m_path(filePath)
{
    ShaderProgramSource src = PharseShader(filePath);
    m_RenderID = CreatShader(src.vertexShader, src.fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_RenderID);
}

void Shader::SetUniformi1(const std::string& name, int value)
{
    glUniform1i(GetLocation(name),value);
}

void Shader::SetUniformf4(const std::string& name,float v1,float v2,float v3,float v4)
{
    glUniform4f(GetLocation(name), v1, v2, v3, v4);
}
void Shader::SetUniformMatf4(const std::string& name,const glm::mat4& mat)
{
    glUniformMatrix4fv(GetLocation(name),1,GL_FALSE,&mat[0][0]);
}
int Shader::GetLocation(const std::string& name)
{
    if (m_UniformLocatonCache.find(name) != m_UniformLocatonCache.end())
        return m_UniformLocatonCache[name];
    int location=glGetUniformLocation(m_RenderID, name.c_str());
    if (location == -1)
        std::cout << "Waring: uniform \"" << name << "\" not exist!";
    else
    {
        m_UniformLocatonCache[name] = location;
    }
    return location;
}
void Shader::Bind() const
{
    GLCall(glUseProgram(m_RenderID));
}

void Shader::UnBind() const
{
    GLCall(glUseProgram(0));
}

unsigned int Shader::ComplieShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //Handle error
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Fail to complie" << (type == GL_VERTEX_SHADER ? " vertex" : " fragment") << " Shader!" << std::endl;
        std::cout << message << std::endl;
        delete[] message;
    }
    return id;
}

unsigned int Shader::CreatShader(const std::string& vertexShader, const std::string& fragmentShader)
{

    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = ComplieShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = ComplieShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    //删除中间文件例如obj,不用glDeattachShader是因为会删除shader源文件给调试造成麻烦。
    glDeleteShader(vs);
    glDeleteShader(fs);


    return program;
}