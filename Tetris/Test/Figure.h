#pragma once
#include "World.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

enum Type { one, two, three, four, five, None };

class Figure
{
public:

    Figure(Type type);
    ~Figure();

    int getType();
    const sf::Vector2i* getCord() const;

    void generateType(Type t);

    void move(int s);
    void fall();
    void fastFall(int field[fieldHeight][fieldWidth]);
    void rotate(int field[fieldHeight][fieldWidth]);


private:
    Type type;
    sf::Vector2i blocks[4];
};