#pragma once

class Texture
{
public:
	Texture(char const* filename, int wrapping, int forma);
	void bind();
	void unbind();
	void activeAndBind(int unit);
private:
	unsigned int ID;
	char* data;
	int width;
	int height;
	int nrChannels;
};