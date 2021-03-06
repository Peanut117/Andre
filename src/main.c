#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>

#include "window.h"
#include "shader.h"
#include "renderer.h"
#include "texture.h"
#include "camera.h"

//TODO mogelijkheid voor meer dan 31 textures
//TODO maak shaders makkelijker
//TODO animation
//TODO post processing
//TODO text
//TODO gui iets
//TODO physics
//TODO particles
//TODO ui iets
//TODO scenes
//TODO audio
//TODO windows compitabel
//TODO multi-threading
//TODO gpu offloading
//TODO profiling

#define WHITE_COLOR (vec4){1.0f, 1.0f, 1.0f, 1.0f}

int main(void)
{
	Window window;
	window.size[0] = 800;
	window.size[1] = 600;
	window.name = "Test";

	//Mkae window
	createWindow(&window, (vec2){500, 500});

	//init glew
	//glewExperimental = GL_TRUE;
	glewInit();

	//set viewport
	glViewport(0, 0, 800, 600);

	glEnable(GL_DEPTH_TEST);

	initRenderer();

	uint32_t shaderProgram = createShaderProgram("shaders/shader.vert", "shaders/shader.frag");

	glUseProgram(shaderProgram);

	//Handle textures
	char* textureFiles[] = {
		"../textures/cock.png",
		"../textures/test.png",
	};

	char* spriteSheet[] = {
		"../textures/"
	};

	uint32_t* textures = generateTextures2D(textureFiles, 2, GL_CLAMP_TO_EDGE, GL_NEAREST);

	int spriteWidth, spriteHeight;

	uint32_t* sprite = generateTexture2DWH(spriteSheet, 1, GL_CLAMP_TO_EDGE, GL_NEAREST, &spriteWidth, &spriteHeight);

	uint32_t whiteTextureData = 0xffffffff;

	uint32_t whiteTextureID;
	glGenTextures(1, &whiteTextureID);
	glBindTexture(GL_TEXTURE_2D, whiteTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &whiteTextureData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(0, whiteTextureID);

	int samplers[32];

	for(int i = 0; i < 32; i++)
	{
		//glBindTextureUnit(i, textures[i]);
		samplers[i] = i;
	}

	unsigned int texLoc = glGetUniformLocation(shaderProgram, "Textures");
	glUniform1iv(texLoc, 32, samplers);

	glBindTextureUnit(1, textures[0]);
	glBindTextureUnit(2, textures[1]);
	glBindTextureUnit(3, sprite[0]);

	//Setup camera
	Camera camera = initCamera();

	camera.projLoc = glGetUniformLocation(shaderProgram, "projection");

	camera.viewLoc = glGetUniformLocation(shaderProgram, "view");

	//main loop
	while(!glfwWindowShouldClose(window.window))
	{
		//Clear screen every loop
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sendViewProjMat(camera);

		//Draw things
		//Atlas spriteAtlas = {3, 1280.0f, 832.0f, 20, 13};
		Atlas spriteAtlas = {3, spriteWidth, spriteHeight, 20, 13};

		//drawSpriteScaled((vec2){50, 50}, 150, spriteAtlas, (vec2){7, 7});
		drawSprite((vec2){50, 50}, spriteAtlas, (vec2){7, 7});
		
		flushRenderer();

		if(glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS)
		{
			camera.pos[1] -= 5;
		}

		if(glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS)
		{
			camera.pos[1] += 5;
		}

		if(glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS)
		{
			camera.pos[0] -= 5;
		}

		if(glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS)
		{
			camera.pos[0] += 5;
		}

		//Swap buffers and poll events
		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}

	free(textures);

	glDeleteProgram(shaderProgram);
	
	quitRenderer();

	glfwTerminate();

	return 0;
}
