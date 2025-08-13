#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Types.h"
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

class Figure;

class World
{
public:

    World();
    ~World();

    bool getBool();
    int getScore();
    bool getStop();
    void figureP();
    void figureM();

    ColorFigure(*getColorField())[fieldWidth]; // метод доступу
    int (*getField())[fieldWidth];              // доступ до поля
    void fixFigure(const Figure* figure);       // зберегти фігуру в полі
    void checkLines();                          // перевірка рядків

private:
    bool needFigure;
    int field[fieldHeight][fieldWidth];         // саме поле
    int score;
    ColorFigure colorField[fieldHeight][fieldWidth];

    //sound
    SoundBuffer bufferLine;
    Sound line;
};