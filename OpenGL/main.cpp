#include "GameInstance.h"

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int width = 1280, height = 720;

	//GLFWwindow* window = glfwCreateWindow(width, width, "Game Of Life", NULL, NULL);
	GLFWwindow* window = glfwCreateWindow(width, height, "Game Of Life", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	{
		GameInstance game{ width, height };

		while (!glfwWindowShouldClose(window))
		{
			glClearColor(.1f, .2f, .4f, .1f);
			glClear(GL_COLOR_BUFFER_BIT);

			processInput(window);

			if (game.update() != 0)
			{
				std::cout << "Error in update prcoess" << std::endl;
				return -1;
			}

			if (game.render() != 0)
			{
				std::cout << "Error in rendering prcoess" << std::endl;
				return -1;
			}

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}
