#include "vbo.h"
#include "error_check.h"

Vbo::Vbo(const void* data, unsigned int size)
{
	GLCALL(glGenBuffers(1, &ID));
	bind();
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

Vbo::~Vbo()
{
	GLCALL(glDeleteBuffers(1, &ID));
}

void Vbo::bind()
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, ID));
}

void Vbo::unbind()
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Vbo::attribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
	GLsizei stride, const void* pointer)
{
	GLCALL(glVertexAttribPointer(index, size, type, normalized, stride, pointer));
	GLCALL(glEnableVertexAttribArray(index));
}