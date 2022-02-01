#include "window.h"

void createWindow(Window* window, vec2 pos)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window->window = glfwCreateWindow(window->size[0], window->size[1], window->name, NULL, NULL);
	if(window->window == NULL)
	{
		printf("Failed to create glfw window\n");
		glfwTerminate();
		exit(-1);
	}

	glfwSetWindowPos(window->window, pos[0], pos[1]);

	glfwMakeContextCurrent(window->window);
};
