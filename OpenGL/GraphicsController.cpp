#include <ft2build.h>
#include FT_FREETYPE_H
#include "GraphicsController.h"

// ---------------------- PRIVATE ---------------------- \\

GraphicsController* GraphicsController::inst = nullptr;

Metadata* GraphicsController::md = nullptr;

std::map<std::string, Shader*> GraphicsController::shaders;

std::map<GLchar, Character> GraphicsController::Characters;

unsigned int GraphicsController::VAO, GraphicsController::VBO, GraphicsController::EBO;

GraphicsController::GraphicsController()
{
    md = Metadata::getInstance();

	shaders["simple"] = (new Shader("simple_shader.vert", "simple_shader.frag"));
	shaders["menu_button"] = (new Shader("menu_button.vert", "menu_button.frag"));

    initFreeType();
}

int GraphicsController::initFreeType()
{
    // FreeType
    // --------
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::GRAPHICS_CONTROLLER::INIT_FREETYTPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, "resources/fonts/arial.ttf", 0, &face)) {
        std::cout << "ERROR::GRAPHICS_CONTROLLER::INIT_FREETYTPE: Failed to load font (Check if included in project!)" << std::endl;
        return -1;
    }

    // set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 48);

    // disable byte-alignment restriction
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // load first 128 characters of ASCII set
    for (unsigned char c = 0; c < 128; c++)
    {
        // Load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::GRAPHICS_CONTROLLER::INIT_FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            face->glyph->bitmap_left,
            face->glyph->bitmap_top,
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

	return 0;
}

// ---------------------- PUBLIC ---------------------- \\

GraphicsController* GraphicsController::getInstance()
{
	if (inst == nullptr)
	{
		inst = new GraphicsController();
	}
	return inst;
}

Shader* GraphicsController::getShader(std::string name)
{
	if (shaders[name] == nullptr)
	{
		std::cout << "ERROR::GRAPHICS_CONTROLLER::GET_SHADER::SHADER_NOT_FOUND" << std::endl;
		return nullptr;
	}
	return shaders[name];
}

void GraphicsController::addShader(std::string shader_name, const char* vertex_shader_file, const char* fragment_shader_file)
{
	shaders[shader_name] = (new Shader(vertex_shader_file, fragment_shader_file));
}

void GraphicsController::normalizeVertex(
    int ivertices[],
    size_t ivertices_size,
    float normalized_vertices[],
    bool colored)
{
    for (int i = 0; i < ivertices_size; i += 6)
    {
        normalized_vertices[i] = 2.f * (float)ivertices[i] / (float)md->getWndWidth();		// x
        normalized_vertices[i + 1] = 2.f * (float)ivertices[i + 1] / (float)md->getWndHeight(); // y
        normalized_vertices[i + 2] = 0.f;											// z
        //normalized_vertex[i+2] = (float)int_vertex[i+2] / Metadata::maxDepth;

        if (colored)
        {
            // Colors
            normalized_vertices[i + 3] = (float)ivertices[i + 3] / 255.f; // r
            normalized_vertices[i + 4] = (float)ivertices[i + 4] / 255.f; // g
            normalized_vertices[i + 5] = (float)ivertices[i + 5] / 255.f; // b
        }
    }
}

//void GraphicsController::draw(std::vector<int> ivertices, size_t size_ivertices, std::vector<unsigned int> indices, size_t size_indices, bool colored)
//{
//    //for (int i = 0; i < size_ivertices; i++)
//    //{
//    //    std::cout << ivertices[i] << std::endl;
//    //}
//
//    float* vertices = new float[size_ivertices];
//    
//    normalizeVertex(ivertices.data(), size_ivertices, vertices, true);
//
//    glBindVertexArray(GraphicsController::VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, GraphicsController::VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GraphicsController::EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices.data()), indices.data(), GL_DYNAMIC_DRAW);
//
//    // Linking Vertex Attributes
//
//    if (colored)
//    {
//        // Position
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//        glEnableVertexAttribArray(0);
//
//        // Color
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//        glEnableVertexAttribArray(1);
//    }
//    else 
//    {
//        // Position
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//        glEnableVertexAttribArray(0);
//    }
//
//    //glBindVertexArray(VAO);
//    //glDrawArrays(GL_TRIANGLES, 0, 3);
//    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glDrawElements(GL_TRIANGLES, size_indices, GL_UNSIGNED_INT, 0);
//
//    GLenum err = glGetError();
//    if (err != GL_NO_ERROR) std::cout << "ERROR::GRAPHICS_CONTROLLER::DRAW: OpenGL error: " << err << std::endl;
//
//}
