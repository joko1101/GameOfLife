#include "util.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void GLClearErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OPENGL ERROR] (" << error << ")" << " - " << function
			<< " " << file << " : " << line << std::endl;
		return false;
	}
	return true;
}

void GLCheckError()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OPENGL ERROR] " << error << std::endl;
	}
}