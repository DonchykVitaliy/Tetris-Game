#pragma once
#include "World.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Types.h"

using namespace std;

class Figure
{
public:

    Figure(Type type, ColorFigure color);
    ~Figure();

    int getType();
    const sf::Vector2i* getCord() const;
    sf::Color getColor() const;
    ColorFigure getColorEnum() const;

    void generateType(Type t);

    void move(int s, int field[fieldHeight][fieldWidth]);
    void fall();
    void fastFall(int field[fieldHeight][fieldWidth]);
    void rotate(int field[fieldHeight][fieldWidth]);


private:
    Type type;
    ColorFigure color;
    sf::Vector2i blocks[4];
};