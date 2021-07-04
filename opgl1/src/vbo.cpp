#include "vbo.h"

Vbo::Vbo(const void* data, unsigned int size)
{
	glGenBuffers(1, &ID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Vbo::~Vbo()
{
	glDeleteBuffers(1, &ID);
}

void Vbo::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void Vbo::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vbo::attribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
	GLsizei stride, const void* pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}