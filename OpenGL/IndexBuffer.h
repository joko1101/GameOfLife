#pragma 
#include <vector>

class IndexBuffer
{
private:

	unsigned int m_rendererID;

	unsigned int m_count;

public:
	IndexBuffer();

	IndexBuffer(const unsigned int* data, unsigned int count);

	~IndexBuffer();

	void setData(const unsigned int* data, unsigned int count);

	void bind() const;

	void unbind() const;

	unsigned int getCount() const;
};

