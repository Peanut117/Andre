#ifndef CAMERA_H
#define CAMERA_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <cglm/cglm.h>

typedef struct Camera {
	vec2 pos;
	mat4 proj;
	mat4 view;
	unsigned int projLoc;
	unsigned int viewLoc;
} Camera;

Camera initCamera();

void sendViewProjMat(Camera camera);

#endif //CAMERA_H
