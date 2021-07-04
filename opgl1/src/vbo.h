#pragma once
#include "GL/glew.h"

class Vbo
{
public:
	Vbo(const void* data, unsigned int size);
	~Vbo();
	void bind();
	void unbind();
	void attribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
		GLsizei stride, const void* pointer);
private:
	unsigned int ID;
};