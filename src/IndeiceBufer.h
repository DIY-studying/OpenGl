#pragma once


class IndeiceBufer
{
private:
	unsigned int m_RenderID;
	int m_Count;

public:
	IndeiceBufer(const void* data,unsigned int count);
	IndeiceBufer(const void* data, unsigned int count, unsigned int usage);

	~IndeiceBufer();
	
	void Bind() const;
	void UnBind() const;
	int GetCount() const;
};

