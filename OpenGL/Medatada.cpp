#include "Metadata.h"

Metadata* Metadata::inst = nullptr;

Metadata::Metadata(
	unsigned int window_width, 
	unsigned int window_height, 
	unsigned int max_depth)
	: wndWidth(window_width)
	, wndHeight(window_height)
	, maxDepth(max_depth)
{

	inst = this;
}

Metadata* Metadata::getInstance()
{
	if (inst == nullptr)
	{
		std::cout << "Initializing with default values." << std::endl;
		inst = new Metadata(1280, 720, 1);
	}
	return inst;
}

Metadata* Metadata::getInstance(
	unsigned int window_width, 
	unsigned int window_height,
	unsigned int max_depth)
{
	if (inst == nullptr)
	{
		inst = new Metadata(window_width, window_height, max_depth);
	}
	return inst;
}

// Getters
unsigned int Metadata::getWndWidth() const { return wndWidth; }
unsigned int Metadata::getWndHeight() const { return wndHeight; }
unsigned int Metadata::getMaxDepth() const { return maxDepth; }

// Setters
void Metadata::resizeWnd(unsigned int window_width, unsigned int window_height)
{
	this->wndWidth = window_width;
	this->wndHeight = window_height;
}

void Metadata::setMaxDepth(unsigned int max_depth)
{
	this->maxDepth = max_depth;
}
