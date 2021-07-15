#ifdef SNAKE_GAME

#pragma once

#include "../engine/vao.h"
#include "../engine/vbo.h"
#include "../engine/ebo.h"
#include "../engine/shader.h"
#include "../engine/window.h"
#include "square.h"


#include <vector>

class Snake
{
public:
	Snake();
	~Snake();
	void update();
	void draw();
	void input(Direction direction);
	void addSquare();
private:
	Shader* squareShader;
	Vao* squareVao;
	Vbo* squareVbo;
	Ebo* squareEbo;
	std::vector<Square*> squares;

};

#endif