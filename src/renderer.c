#include "renderer.h"

#define WHITE_COLOR (vec4){1.0f, 1.0f, 1.0f, 1.0f}

uint32_t quadCount = 0;
const uint32_t quadSize = sizeof(Vertex) * 4;
const uint32_t maxQuadCount = 1000;
const uint32_t maxVertexCount = maxQuadCount * 4;
const uint32_t maxIndexCount = maxQuadCount * 6;
const uint32_t maxTextures = 32;

unsigned int vao, vbo, ebo;

Vertex vertices[4];

void initRenderer()
{
	uint32_t* indices = malloc(maxIndexCount * sizeof(uint32_t));

	uint32_t offset = 0;
	for (uint32_t i = 0; i < maxIndexCount; i += 6)
	{
		indices[i] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	//Maak en doe buffer dingen
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, maxVertexCount * sizeof(struct Vertex), NULL, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxIndexCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);

	free(indices);

	//Stuur vertex data dingen naar shaders
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2 + sizeof(vec4) + sizeof(float), 0); 

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2 + sizeof(vec4) + sizeof(float), (void*)(sizeof(vec2))); 

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2 + sizeof(vec4) + sizeof(float), (void*)(sizeof(vec2) + sizeof(vec4))); 

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2 + sizeof(vec4) + sizeof(float), (void*)(sizeof(vec2) * 2 + sizeof(vec4))); 
}

void flushRenderer()
{
	if(quadCount == 0)
		return;

	glDrawElements(GL_TRIANGLES, maxIndexCount, GL_UNSIGNED_INT, 0);

	quadCount = 0;
}

void quitRenderer()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void drawQuadSC(vec2 pos, vec2 size, vec4 color)
{
	drawQuad(pos, size, 0, color);
}

void drawSquareSC(vec2 pos, float size, vec4 color)
{
	drawQuadSC(pos, (vec2){size, size}, color);
}

void drawQuad(vec2 pos, vec2 size, uint32_t texID, vec4 color)
{
	drawQuadTP((vec4){pos[0], pos[1], pos[0] + size[0], pos[1] + size[1]}, (vec4){0.0f, 0.0f, 1.0f, 1.0f}, texID, color);
}

void drawQuadTP(vec4 pos, vec4 texCoords, uint32_t texID, vec4 color)
{
	if(quadCount >= maxQuadCount)
		flushRenderer();

	vertices[0].pos[0] = pos[0];
	vertices[0].pos[1] = pos[1];
	vertices[1].pos[0] = pos[2];
	vertices[1].pos[1] = pos[1];
	vertices[2].pos[0] = pos[2];
	vertices[2].pos[1] = pos[3];
	vertices[3].pos[0] = pos[0];
	vertices[3].pos[1] = pos[3];

	vertices[0].texCoords[0] = texCoords[0];
	vertices[0].texCoords[1] = texCoords[1];
	vertices[1].texCoords[0] = texCoords[0] + texCoords[2];
	vertices[1].texCoords[1] = texCoords[1];
	vertices[2].texCoords[0] = texCoords[0] + texCoords[2];
	vertices[2].texCoords[1] = texCoords[1] + texCoords[3];
	vertices[3].texCoords[0] = texCoords[0];
	vertices[3].texCoords[1] = texCoords[1] + texCoords[3];

	for(int i = 0; i < 4; i++) { glm_vec4_copy(color, vertices[i].color);
		vertices[i].texID = texID;
	}

	glBufferSubData(GL_ARRAY_BUFFER, quadCount * quadSize, sizeof(vertices), vertices);

	quadCount++;
}

void drawSquare(vec2 pos, uint32_t size, uint32_t texID, vec4 color)
{
	drawQuad(pos, (vec2){size, size}, texID, color);
}

void drawSprite(vec2 pos, Atlas atlas, vec2 spritePos)
{
	float spriteWidth = atlas.width / atlas.freqWidth;
	float spriteHeight = atlas.height / atlas.freqHeight;

	drawQuadTP((vec4){pos[0], pos[1], pos[0] + spriteWidth, pos[1] + spriteHeight},
				(vec4){
				(spritePos[0] * spriteWidth) / atlas.width, (spritePos[1] * spriteHeight) / atlas.height,
				spriteWidth / atlas.width, spriteHeight / atlas.height
				},
				atlas.texID, WHITE_COLOR);
}

void drawSpriteScaled(vec2 pos, uint32_t size, Atlas atlas, vec2 spritePos)
{
	float spriteWidth = atlas.width / atlas.freqWidth;
	float spriteHeight = atlas.height / atlas.freqHeight;

	float ratio = spriteWidth / spriteHeight;

	drawQuadTP((vec4){pos[0], pos[1], pos[0] + size * ratio, pos[1] + size},
				(vec4){
				(spritePos[0] * spriteWidth) / atlas.width, (spritePos[1] * spriteHeight) / atlas.height,
				spriteWidth / atlas.width, spriteHeight / atlas.height
				},
				atlas.texID, WHITE_COLOR);
}
