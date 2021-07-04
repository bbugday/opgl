#include "vao.h"

#include <GL/glew.h>

Vao::Vao()
{
	glGenVertexArrays(1, &ID);
	bind();
}

Vao::~Vao()
{	
	glDeleteVertexArrays(1, &ID);
}

void Vao::bind()
{
	glBindVertexArray(ID);
}

void Vao::unbind()
{
	glBindVertexArray(0);
}

