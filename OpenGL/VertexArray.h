#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <glad/glad.h>

class VertexArray
{
private:
	unsigned int m_rendererID;

public:
	VertexArray()
		: m_rendererID(0)
	{
		glGenVertexArrays(1, &m_rendererID);
	}

	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		vb.bind();
		const auto& elements = layout.getElements();
		unsigned int offset = 0;

		for (int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
			offset += element.count * VertexBufferElement::getSizeOfType(element.type);
		}
	}

	void bind()
	{

	}
};