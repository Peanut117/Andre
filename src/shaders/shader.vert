#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in float texIndex;

out vec4 Color;
out vec2 TexCoord;
out float TexIndex;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	Color = color;
	TexCoord = texCoord;
	TexIndex = texIndex;
	gl_Position = projection * view * vec4(position, 0.0, 1.0);
}
