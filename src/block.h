#ifndef BLOCK_H
#define BLOCK_h

#define GLEW_STATIC
#include <GL/glew.h>

//TODO vind een oplossing dat dit niet hoeft
#define CGLM_ALL_UNALIGNED
#include <cglm/cglm.h>

#include "vertex.h"

void drawRectangleSC(vec2 pos, vec2 size, vec4 color);

void drawSquareSC(vec2 pos, float size, vec4 color);

void drawRectangle(vec2 pos, vec2 size, vec4 texCoords, uint32_t texID, vec4 color);

void drawRectangleTP(vec4 pos, vec4 texCoords, uint32_t texID, vec4 color);

void drawSquare(vec2 pos, uint32_t size, vec4 texCoords, uint32_t texID, vec4 color);

#endif //BLOCK_H
