#ifndef VERTEX_H
#define VERTEX_H

#include <cglm/cglm.h>

typedef struct Vertex {
	vec2 pos;
	vec4 color;
	vec2 texCoords;
	float texID;
} Vertex;

#endif //VERTEX_H
