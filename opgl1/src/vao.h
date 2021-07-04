#pragma once

class Vao
{
public:
	Vao();
	~Vao();
	void bind();
	void unbind();
private:
	unsigned int ID;
};