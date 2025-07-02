#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearErrors();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void framebuffer_size_callback(GLFWwindow * window, int width, int height);

void processInput(GLFWwindow * window);

void GLClearErrors();

bool GLLogCall(const char* function, const char* file, int line);

void GLCheckError();