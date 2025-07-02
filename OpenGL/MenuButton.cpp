#include <glad/glad.h>
#include "MenuButton.h"


MenuButton::MenuButton(int x, int y, int width, int height, std::string text)
    : x(x), y(y), width(width), height(height), isSelected(false), isPressed(false), text(text)
{
}

void MenuButton::checkHover(int mouseX, int mouseY)
{
    this->isSelected = (
        mouseX >= x && mouseX <= x + width &&
        mouseY >= y && mouseY <= y + height
        );
}

void MenuButton::checkMousePress(bool leftMouseDown)
{
    this->isPressed = this->isSelected && leftMouseDown;
}

void MenuButton::checkSelected()
{
    // Stub: Implement selection logic if needed
    //return isPressed;
}

void MenuButton::checkKeyboardPress(bool enterPressed)
{
    this->isPressed = this->isSelected && enterPressed;
}

void MenuButton::onClick(std::function<void(int)> callback)
{
    // Stub: Add click effect logic (e.g., trigger action)
}

void MenuButton::update()
{
    // Stub: Add update logic if needed (e.g., animation)
}

void MenuButton::draw()
{
	//glBindVertexArray(VAO);

	//int ivertices[] = {
	//	x, y, 1, r, g, b,
	//	x, y + width, 1, r, g, b,
	//	x + width, y + width, 1, r, g, b,
	//	x + width, y, 1, r, g, b,
	//};

	//const size_t SIZE_VERTICES = 24;

	//float fvertices[SIZE_VERTICES];

	//grphCtrl->normalizeVertex(ivertices, SIZE_VERTICES, fvertices, true);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(fvertices), fvertices, GL_DYNAMIC_DRAW);

	//unsigned int indices[] =
	//{
	//	0, 1, 2,
	//	0, 2, 3
	//};

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//// Bind vert attrib

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 //   if (isSelected)
 //   {
 //   }
 //   else if (isPressed)
 //   {
 //   }
 //   else
 //   {
 //   }
}