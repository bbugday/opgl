#include "ebo.h"
#include "error_check.h"

#include <GL/glew.h>

Ebo::Ebo(const void* data, unsigned int size)
{
	GLCALL(glGenBuffers(1, &ID));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

Ebo::~Ebo()
{
	GLCALL(glDeleteBuffers(1, &ID));
}

void Ebo::bind()
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
}

void Ebo::unbind()
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
