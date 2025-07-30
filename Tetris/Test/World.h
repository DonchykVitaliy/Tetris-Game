#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

const int fieldWidth = 10;
const int fieldHeight = 15;


enum Direction { Up, Down, Left, Right, No };

class Figure;

class World
{
public:

    World();
    ~World();

    bool getBool();
    void figureP();
    void figureM();

    int (*getField())[fieldWidth];              // доступ до поля
    void fixFigure(const Figure* figure);       // зберегти фігуру в полі

private:
    bool needFigure;
    int field[fieldHeight][fieldWidth];         // саме поле
};