#ifdef SNAKE_GAME

#pragma once

#include "game_consts.h"	

struct Square
{
	Square(float x, float y, Direction direction);
	void move();
	float x;
	float y;
	static float velocity;
	Direction direction;
};

#endif