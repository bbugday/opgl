#ifdef SNAKE_GAME

#pragma once

enum class Direction {LEFT = 1, RIGHT = -1, UP = 2, DOWN = -2};

const float SNAKE_START_POSITION_X = 0;

const float SNAKE_START_POSITION_Y = 0;

const Direction SNAKE_START_DIRECTION = Direction::UP;

const float SQUARE_LENGTH = 0.05f;

#endif