#ifndef RENDERER_H
#define RENDERER_H

#define GLEW_STATIC
#include <GL/glew.h>

//TODO vind een oplossing dat dit niet hoeft
#define CGLM_ALL_UNALIGNED
#include <cglm/cglm.h>

#include "shader.h"

typedef struct Vertex {
	vec2 pos;
	vec4 color;
	vec2 texCoords;
	float texID;
} Vertex;

typedef struct Atlas {
	float texID;
	int width;
	int height;
	uint32_t freqWidth; //Aantal sprites in de breedte
	uint32_t freqHeight; //Aantal sprites in de hoogte
} Atlas;

void initRenderer();

void flushRenderer();

void quitRenderer();

void drawQuadSC(vec2 pos, vec2 size, vec4 color);

void drawSquareSC(vec2 pos, float size, vec4 color);

void drawQuad(vec2 pos, vec2 size, uint32_t texID, vec4 color);

void drawQuadTP(vec4 pos, vec4 texCoords, uint32_t texID, vec4 color);

void drawSquare(vec2 pos, uint32_t size, uint32_t texID, vec4 color);

void drawSprite(vec2 pos, Atlas atlas, vec2 spritePos);

void drawSpriteScaled(vec2 pos, uint32_t size, Atlas atlas, vec2 spritePos);

#endif //RENDERER_H
