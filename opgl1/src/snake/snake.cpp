#ifdef SNAKE_GAME

#include "snake.h"
#include "../engine/error_check.h"

#include <GLFW/glfw3.h>
#include <iostream>


Snake::Snake() : squares(1, new Square(SNAKE_START_POSITION_X, SNAKE_START_POSITION_Y, SNAKE_START_DIRECTION))
{
    const float halfLength = SQUARE_LENGTH / 2;

    const float squareVertex[] = {
         halfLength,  halfLength,
        -halfLength,  halfLength,
        -halfLength, -halfLength,
         halfLength, -halfLength
    };

    unsigned const int squareIndices[] = {
        0, 1, 3,
        1, 2, 3
    };
    
    squareShader = new Shader("res/shaders/squareVertex.glsl", "res/shaders/squareFragment.glsl");
    squareVao = new Vao();
    squareVbo = new Vbo(squareVertex, sizeof(squareVertex));
    squareVbo->attribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    squareEbo = new Ebo(squareIndices, sizeof(squareIndices));

    squareVao->unbind();
    squareVbo->unbind();
    squareEbo->unbind();

}

Snake::~Snake() {
    delete squareShader;
    delete squareVao;
    delete squareVbo;
    delete squareEbo;
}

void Snake::draw()
{
    squareVao->bind();

    squareShader->use();

    for (unsigned int i = 0; i < squares.size(); i++)
    {
        squareShader->setVec2Float("offset", squares[i]->x, squares[i]->y);

        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    }
}

void Snake::update()
{
    for (auto square : squares)
    {
        square->move();
    }

    for (int i = squares.size() - 1; i > 0; i--)
    {
        squares[i]->direction = squares[i - 1]->direction;
    }

}

void Snake::input(Direction direction)
{
    if (-static_cast<int>(direction) != static_cast<int>(squares[0]->direction))
    {
        squares[0]->direction = direction;
    }
}

void Snake::addSquare()
{
    Square *lastSquare = squares.back();

    float newX = lastSquare->x;
    float newY = lastSquare->y;

    switch (lastSquare->direction)
    {
        case Direction::LEFT:
            newX = lastSquare->x + SQUARE_LENGTH;
            break;
        case Direction::RIGHT:
            newX = lastSquare->x - SQUARE_LENGTH;
            break;
        case Direction::UP:
            newY = lastSquare->y - SQUARE_LENGTH;
            break;
        case Direction::DOWN:
            newY = lastSquare->y + SQUARE_LENGTH;
            break;
    }

    squares.push_back(new Square(newX, newY, lastSquare->direction));
}

#endif

