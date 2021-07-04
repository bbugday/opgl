#pragma once

class Ebo
{
public:
	Ebo(const void* data, unsigned int size);
	~Ebo();
	void bind();
	void unbind();
private:
	unsigned int ID;
};