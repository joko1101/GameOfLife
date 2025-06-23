#pragma once
#include "IShape.h"

static class Point: public IShape
{
public:

    static void draw(int x, int y, int width, RECT rc, HDC hdc, COLORREF color)
	{

        // Create a pen.            
        HPEN blackPen = CreatePen(PS_SOLID, width, color);

        // Select the pen.
        SelectObject(hdc, blackPen);

        // Draw a rectangle.
        Rectangle(
            hdc,
            rc.left + x,
            rc.top + y,
            rc.left + x + width + 1,
            rc.top + y + width + 1);

        DeleteObject(blackPen);

	}
};

