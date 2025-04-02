#pragma once
#include <string>
#include<unordered_map>
#include<glm/glm.hpp>

struct ShaderProgramSource
{
	std::string vertexShader;
	std::string fragmentShader;
};
class Shader
{
private:
	unsigned int m_RenderID;
	std::string m_path;
	std::unordered_map<std::string, int> m_UniformLocatonCache;
public:
	Shader(const std::string& filePath);
	~Shader();
	void SetUniformi1(const std::string& name,int i1);
	void SetUniformf4(const std::string& name, float v1, float v2, float v3, float v4);
	void SetUniformMatf4(const std::string& name,const glm::mat4& matrix);
	
	void Bind() const;
	void UnBind() const;
private:
	int GetLocation(const std::string& name);
	ShaderProgramSource PharseShader(const std::string& path);
	unsigned int ComplieShader(unsigned int type, const std::string& source);
	unsigned int CreatShader(const std::string& vertexShader, const std::string& fragmentShader);
};

