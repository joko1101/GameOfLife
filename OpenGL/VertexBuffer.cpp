#include <glad/glad.h>
#include "VertexBuffer.h"
#include "util.h"
#include <iostream>

VertexBuffer::VertexBuffer()
	: m_rendererID()
{}

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	: m_rendererID()
{
	GLCall(glGenBuffers(1, &m_rendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
	std::cout << "Vertex Buffer constructed" << std::endl;
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_rendererID));
}

void VertexBuffer::setData(const void* data, unsigned int size) const
{
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

void VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}