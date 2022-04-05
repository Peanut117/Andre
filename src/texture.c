#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

//Maakt op het moment gebruik van de heup. ik weet niet of dit impact heeft op de performance
uint32_t* generateTextures2D(char** file, uint32_t number, int wrap, int filter)
{
	uint32_t* textures = calloc(number, sizeof(uint32_t));
	
	glGenTextures(number, textures);

	int width, height, nrChannels;
	unsigned char* data;

	for(int i = 0; i < number; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);

		/*
		* GL_REPEAT: The integer part of the coordinate will be ignored and a repeating pattern is formed.
		* GL_MIRRORED_REPEAT: The texture will also be repeated, but it will be mirrored when the integer part of the coordinate is odd.
		* GL_CLAMP_TO_EDGE: The coordinate will simply be clamped between 0 and 1.
		* GL_CLAMP_TO_BORDER: The coordinates that fall outside the range will be given a specified border color.
		*/

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

		/*
		* GL_NEAREST: Returns the pixel that is closest to the coordinates.
		* GL_LINEAR: Returns the weighted average of the 4 pixels surrounding the given coordinates.
		* GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR: Sample from mipmaps instead.
		*/
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

		data = stbi_load(file[i], &width, &height, &nrChannels, 0);

		if(data)
		{
			if(nrChannels == 3)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			} else if(nrChannels == 4)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			printf("Failed to load texture");
			return 0;
		}

		stbi_image_free(data);
	}

	return textures;
}

uint32_t* generateTexture2DWH(char** file, uint32_t number, int wrap, int filter, int* width, int* height)
{
	uint32_t* textures = calloc(number, sizeof(uint32_t));
	
	glGenTextures(number, textures);

	int nrChannels;
	unsigned char* data;

	for(int i = 0; i < number; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

		data = stbi_load(file[i], width, height, &nrChannels, 0);

		if(data)
		{
			if(nrChannels == 3)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *width, *height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			} else if(nrChannels == 4)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
			//glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			printf("Failed to load texture");
			return 0;
		}

		stbi_image_free(data);
	}

	return textures;
}
