#include "block.h"

void drawRectangleSC(vec2 pos, vec2 size, vec4 color)
{
	Vertex vertices[4];

	vertices[0].pos[0] = pos[0];
	vertices[0].pos[1] = pos[1];
	vertices[1].pos[0] = pos[0] + size[0];
	vertices[1].pos[1] = pos[1];
	vertices[2].pos[0] = pos[0] + size[0];
	vertices[2].pos[1] = pos[1] + size[1];
	vertices[3].pos[0] = pos[0];
	vertices[3].pos[1] = pos[1] + size[1];

	for(int i = 0; i < 4; i++)
	{
		glm_vec4_copy(color, vertices[i].color);
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void drawSquareSC(vec2 pos, float size, vec4 color)
{
	drawRectangleSC(pos, (vec2){size, size}, color);
}

void drawRectangle(vec2 pos, vec2 size, vec4 texCoords, uint32_t texID, vec4 color)
{
	drawRectangleTP((vec4){pos[0], pos[1], pos[0] + size[0], pos[1] + size[1]}, texCoords, texID, color);
}

void drawRectangleTP(vec4 pos, vec4 texCoords, uint32_t texID, vec4 color)
{
	Vertex vertices[4];

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

	for(int i = 0; i < 4; i++)
	{
		glm_vec4_copy(color, vertices[i].color);
		vertices[i].texID = texID;
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void drawSquare(vec2 pos, uint32_t size, vec4 texCoords, uint32_t texID, vec4 color)
{
	drawRectangle(pos, (vec2){size, size}, texCoords, texID, color);
}
