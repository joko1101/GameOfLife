#include <glad/glad.h>
#include "IndexBuffer.h"
#include "util.h"
#include <iostream>

IndexBuffer::IndexBuffer()
	: m_rendererID()
	, m_count()
{}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_rendererID()
	, m_count()
{
	GLCall(glGenBuffers(1, &m_rendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW))
	std::cout << "Index Buffer constructed" << std::endl;
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_rendererID));
}

void IndexBuffer::setData(const unsigned int* data, unsigned int count)
{
	m_count = count;
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW))
}

void IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

void IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::getCount() const
{
	return this->m_count;
}

