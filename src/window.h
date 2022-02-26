#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>

#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

typedef struct Window {
	GLFWwindow* window;
	vec2 size;
	char* name;
} Window;

void createWindow(Window* window, vec2 pos);

#endif //WINDOW_H
