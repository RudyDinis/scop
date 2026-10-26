#ifndef TEXTURE_CLASS_HPP
#define TEXTURE_CLASS_HPP

#include <glad/gl.h>
#include "shaders/shaderClass.hpp"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};

#endif