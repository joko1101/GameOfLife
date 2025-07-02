#pragma once
#include <iostream>
#include <functional>

class MenuButton
{

private:
	int x, y, width, height;
	bool isSelected;
	bool isPressed;
	std::string text;

public:
	MenuButton(int x, int y, int width, int height, std::string text);

	void checkHover(int mouseX, int mouseY);

	void checkMousePress(bool leftMouseDown);

	void checkSelected();

	void checkKeyboardPress(bool leftMouseDown);

	void onClick(std::function<void(int)> callback);

	void update();

	void draw();
};

