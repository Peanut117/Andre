#version 330 core

in vec4 Color;
in vec2 TexCoord;
in float TexIndex;

out vec4 outColor;

uniform sampler2D Textures[2];

void main()
{
	int index = int(TexIndex);
	outColor = texture(Textures[index], TexCoord) * vec4(Color);
}
