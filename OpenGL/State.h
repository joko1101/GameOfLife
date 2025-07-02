#pragma once
#include "Grid.h"
class State
{
private:

	std::map<unsigned int, std::string> shaderPrograms;

protected:

	Metadata* md;

public:
	State(Metadata* md): md(md) {};

	~State()
	{
		this->md = nullptr;

		//Todo: Delete Shader Programs???
	};

	virtual void update() = 0;

	virtual void draw() = 0;
};

