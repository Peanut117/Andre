#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>

#include "window.h"
#include "shader.h"
#include "block.h"
#include "vertex.h"
#include "texture.h"
#include "camera.h"

//TODO batch renderer
//TODO texture atlas
//TODO animation
//TODO maak shaders makkelijker
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

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int shaderProgram;

	if(!(shaderProgram = createShaderProgram("shaders/shader.vert", "shaders/shader.frag")));

	glUseProgram(shaderProgram);

	//Maak en doe buffer dingen
	unsigned int vao, vbo, ebo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct Vertex) * 50, NULL, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Stuur vertex data dingen naar shaders
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2 + sizeof(vec4) + sizeof(float), 0); 

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2 + sizeof(vec4) + sizeof(float), (void*)(sizeof(vec2))); 

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2 + sizeof(vec4) + sizeof(float), (void*)(sizeof(vec2) + sizeof(vec4))); 

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2 + sizeof(vec4) + sizeof(float), (void*)(sizeof(vec2) * 2 + sizeof(vec4))); 

	//Handle textures
	char* textureFiles[] = {
		"../textures/cock.png",
		"../textures/test.png"
	};

	uint32_t* textures = generateTextures2D(textureFiles, 2, GL_CLAMP_TO_EDGE, GL_LINEAR);

	glBindTextureUnit(0, textures[0]);
	glBindTextureUnit(1, textures[1]);

	unsigned int texLoc = glGetUniformLocation(shaderProgram, "Textures");
	int samplers[2] = {0, 1};
	glUniform1iv(texLoc, 2, samplers);

	//Setup camera
	Camera camera = initCamera();

	camera.projLoc = glGetUniformLocation(shaderProgram, "projection");

	camera.viewLoc = glGetUniformLocation(shaderProgram, "view");

	//main loop
	while(!glfwWindowShouldClose(window.window))
	{
		//Clear screen every loop
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		sendViewProjMat(camera);

		//FIXME maak een solid color shader en bind deze aan drawSC
		//Draw things
		drawSquare((vec2){250, 175}, 150, (vec4){0.0f, 0.0f, 1.0f, 1.0f}, 0, (vec4){1.0f, 1.0f, 1.0f, 1.0f});
		drawSquare((vec2){450, 175}, 120, (vec4){0.0f, 0.0f, 1.0f, 1.0f}, 1, (vec4){1.0f, 1.0f, 1.0f, 1.0f});

		//Swap buffers and poll events
		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);
	
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	free(textures);

	glfwTerminate();

	return 0;
}
