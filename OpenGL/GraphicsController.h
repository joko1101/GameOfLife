#pragma once
#include <iostream>
#include <map>
#include "Shader.h"
#include <vector>
#include "Metadata.h"

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	unsigned int Width;     // Width of glyph
	unsigned int Height;    // Height of glyph
	int BearingX;           // Offset to left of glyph
	int BearingY;           // Offset from baseline to top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class GraphicsController
{
private:

	static GraphicsController* inst;

	static Metadata* md;

	static std::map<std::string, Shader*> shaders;

	static std::map<GLchar, Character> Characters;


	GraphicsController();

	static int initFreeType();

public:
	static unsigned int VAO, VBO, EBO;

	static GraphicsController* getInstance();

	static Shader* getShader(std::string name);

	static void addShader(std::string shader_name, const char* vertex_shader_file, const char* fragment_shader_file);

	static void normalizeVertex(
		int ivertices[],
		size_t ivertices_size,
		float normalized_vertices[],
		bool colored);

	//static void draw(std::vector<int> ivertices, size_t size_ivertices, std::vector<unsigned int> indices, size_t size_indices, bool colored);

};

