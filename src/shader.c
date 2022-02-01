#define GLEW_STATIC
#include <GL/glew.h>

#include "shader.h"

char* getFileContent(const char* file)
{
	char* buffer = 0;
	long length;

	if(access(file, F_OK) != 0)
	{
		printf("file doesn't exist or can't be read: %s\n", file);
		return 0;
	}

	FILE* f = fopen(file, "r");

	if(file)
	{
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = malloc(length + 1);
		if(buffer)
		{
			fread(buffer, 1, length, f);
		}
		fclose(f);

		buffer[length] = '\0';
	}

	if(buffer)
	{
		return buffer;
	}
	else
	{
		printf("Failed to read from file: %s\n", file);
		return 0;
	}
}

unsigned int compileShader(const char* file, GLenum type)
{
	const char* shaderCode;
	if(!(shaderCode = getFileContent(file)))
		return 0;

	unsigned int shader;
	int success;
	char infoLog[512];

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("Failed to compile shader:\n%s\n", infoLog);
	}

	return shader;
}

unsigned int createShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	const char* vertexShaderCode;
	if(!(vertexShaderCode = getFileContent(vertexFile)))
		return 0;

	const char* fragmentShaderCode;
	if(!(fragmentShaderCode = getFileContent(fragmentFile)))
		return 0;

	unsigned int vertex, fragment, ID;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		printf("Failed to compile vertex shader:\n%s\n", infoLog);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		printf("Failed to compile fragment shader:\n%s\n", infoLog);
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		printf("Failed to link shader program:\n%s\n", infoLog);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return ID;
}

unsigned int createShaderProgramG(const char* vertexFile, const char* fragmentFile, const char* geometryFile)
{
	const char* vertexShaderCode;
	if(!(vertexShaderCode = getFileContent(vertexFile)))
		return 0;

	const char* fragmentShaderCode;
	if(!(fragmentShaderCode = getFileContent(fragmentFile)))
		return 0;

	const char* geometryShaderCode;
	if(!(geometryShaderCode = getFileContent(geometryFile)))
		return 0;

	unsigned int vertex, fragment, geometry, ID;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		printf("Failed to compile vertex shader:\n%s\n", infoLog);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		printf("Failed to compile fragment shader:\n%s\n", infoLog);
	}

	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry, 1, &geometryShaderCode, NULL);
	glCompileShader(geometry);
	glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(geometry, 512, NULL, infoLog);
		printf("Failed to compile geometry shader:\n%s\n", infoLog);
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glAttachShader(ID, geometry);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		printf("Failed to link shader program:\n%s\n", infoLog);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteShader(geometry);

	return ID;
}
