#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* getFileContent(const char* file);
unsigned int compileShader(const char* file, GLenum type);
unsigned int createShaderProgram(const char* vertexFile, const char* fragmentFile);
unsigned int createShaderProgramG(const char* vertexFile, const char* fragmentFile, const char* geometryFile);

#endif //SHADER_H
