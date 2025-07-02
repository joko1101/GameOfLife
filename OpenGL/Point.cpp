#include "util.h"
#include "Point.h"


// --------------------------- PRIVATE ---------------------------- \\


void Point::initGlObjects()
{
}

// ---------------------------- PUBLIC ----------------------------- \\


Point::Point(int x, int y, int width, int r, int b, int g)
	: x(x), y(y), width(width), r(r), g(g), b(b)
{
	md = Metadata::getInstance();

	grphCtrl = GraphicsController::getInstance();
}

Point::~Point()
{
	md, grphCtrl = nullptr;
}

void Point::draw()
{
	//va = VertexArray();
	GLCall(glGenVertexArrays(1, &grphCtrl->VAO));
	GLCall(glGenBuffers(1, &grphCtrl->VBO));
	GLCall(glGenBuffers(1, &grphCtrl->EBO));

	GLCall(glBindVertexArray(grphCtrl->VAO));

	// VertexBuffer
	int ivertices[] = {
		x, y, 1, r, g, b,
		x, y + width, 1, r, g, b,
		x + width, y + width, 1, r, g, b,
		x + width, y, 1, r, g, b,
	};

	const unsigned int SIZE_VERTICES = 24;

	float fvertices[SIZE_VERTICES];

	grphCtrl->normalizeVertex(ivertices, SIZE_VERTICES, fvertices, true);

	//vb = VertexBuffer(fvertices, SIZE_VERTICES);

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, grphCtrl->VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, SIZE_VERTICES, fvertices, GL_DYNAMIC_DRAW));

	// IndexBuffer
	unsigned int indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	//ib = IndexBuffer(indices, 6);
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grphCtrl->EBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_DYNAMIC_DRAW));

	// Attribute Arrays
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));

	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));


	//Draw
	//grphCtrl->getShader("simple")->use();

	//GLCall(glBindVertexArray(VAO));
	//ib.bind();

	GLCall(glBindVertexArray(grphCtrl->VAO));
	//GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grphCtrl->EBO));
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

	GLCall(glDeleteVertexArrays(1, &grphCtrl->VAO));
	GLCall(glDeleteBuffers(1, &grphCtrl->VBO));
	GLCall(glDeleteBuffers(1, &grphCtrl->EBO));
}