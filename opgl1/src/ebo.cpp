#include "ebo.h"

#include <GL/glew.h>

Ebo::Ebo(const void* data, unsigned int size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Ebo::~Ebo()
{
	glDeleteBuffers(1, &ID);
}

void Ebo::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void Ebo::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
