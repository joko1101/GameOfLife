#pragma once
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GraphicsController.h"
#include "IShape.h"

class Point: public IShape
{
private:
	Metadata* md;

	GraphicsController* grphCtrl;

	//VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;

	int x, y, width, r, g, b;

	void initGlObjects();

public:
	Point(int x, int y, int width, int r, int b, int g);

	~Point();

	void draw();
};
