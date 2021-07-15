#include "vao.h"
#include "error_check.h"

#include <GL/glew.h>

Vao::Vao()
{
	GLCALL(glGenVertexArrays(1, &ID));
	bind();
}

Vao::~Vao()
{	
	GLCALL(glDeleteVertexArrays(1, &ID));
}

void Vao::bind()
{
	GLCALL(glBindVertexArray(ID));
}

void Vao::unbind()
{
	GLCALL(glBindVertexArray(0));
}

