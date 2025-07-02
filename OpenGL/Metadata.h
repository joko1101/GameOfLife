#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <map>

class Metadata
{
private:
	static Metadata* inst;

	unsigned int wndWidth, wndHeight, maxDepth;

	std::map<std::string, unsigned int> shaders;

	Metadata(
		unsigned int window_width, 
		unsigned int window_height, 
		unsigned int max_depth);

public:
	static Metadata* getInstance();

	static Metadata* getInstance(
		unsigned int window_width,
		unsigned int window_height,
		unsigned int max_depth);

	unsigned int getWndWidth() const;

	unsigned int getWndHeight() const;

	unsigned int getMaxDepth() const;

	void resizeWnd(
		unsigned int window_width,
		unsigned int window_height);

	void setMaxDepth(unsigned int max_depth);
};