#pragma once
#include <vector>

#include<glad/glad.h>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(const unsigned int type)
	{
		switch(type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_elements;

	unsigned int m_stride = 0;

public:

	VertexBufferLayout()
	{
	}

	template<typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
	}

	std::vector<VertexBufferElement> getElements() const
	{
		return m_elements;
	}

	unsigned int getStride() const
	{
		return m_stride;
	}

	void bind()
	{
	}

	void unbind()
	{
	}
};