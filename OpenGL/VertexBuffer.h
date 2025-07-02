#pragma once
#include <vector>

class VertexBuffer
{
private:

	unsigned int m_rendererID;

public:

	VertexBuffer();

	VertexBuffer(const void* data, unsigned int size);

	~VertexBuffer();

	void setData(const void* data, unsigned int size) const;

	void bind() const;

	void unbind() const;
};