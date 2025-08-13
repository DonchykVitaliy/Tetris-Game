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

    ColorFigure(*getColorField())[fieldWidth]; // ����� �������
    int (*getField())[fieldWidth];              // ������ �� ����
    void fixFigure(const Figure* figure);       // �������� ������ � ���
    void checkLines();                          // �������� �����

private:
    bool needFigure;
    int field[fieldHeight][fieldWidth];         // ���� ����
    int score;
    ColorFigure colorField[fieldHeight][fieldWidth];

    //sound
    SoundBuffer bufferLine;
    Sound line;
};