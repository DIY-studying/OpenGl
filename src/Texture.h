#pragma once
#include <string>


class Texture
{
private:
	unsigned int m_RenderID;
	std::string m_filePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(std::string filePath);
	~Texture();

	void Bind(unsigned int slot=0) const;
	void UnBind() const;

};

