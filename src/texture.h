#ifndef TEXTURE_H
#define TEXTURE_H

#define GLEW_STATIC
#include <GL/glew.h>

uint32_t* generateTextures2D(char** file, uint32_t number, int wrap, int filter);

uint32_t* generateTexture2DWH(char** file, uint32_t number, int wrap, int filter, int* width, int* height);

#endif //TEXTURE_H
