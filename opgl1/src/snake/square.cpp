#ifdef SNAKE_GAME

#include "square.h"

#include <iostream>

float Square::velocity = SQUARE_LENGTH;

Square::Square(float x, float y, Direction direction) :
	x(x), y(y), direction(direction) 
{}

void Square::move()
{
	switch (direction)
	{
	case Direction::LEFT:
		x -= velocity;
		break;
	case Direction::RIGHT:
		x += velocity;
		break;
	case Direction::UP:
		y += velocity;
		break;
	case Direction::DOWN:
		y -= velocity;
		break;
	}
}

#endif