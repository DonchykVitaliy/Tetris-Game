#include "World.h"
#include "Figure.h"


using namespace std;
    //****
    World::World()
    {
        needFigure = true;

        // Очистити поле
        for (int y = 0; y < fieldHeight; y++)
            for (int x = 0; x < fieldWidth; x++)
                field[y][x] = 0;
    }

    World::~World() {}

    bool World::getBool()
    {
        return needFigure;
    }

    void World::figureP()
    {
        needFigure = true;
    }

    void World::figureM()
    {
        needFigure = false;
    }

    int(*World::getField())[fieldWidth]
    {
        return field;
    }

        void World::fixFigure(const Figure* figure)
    {
        const sf::Vector2i* blocks = figure->getCord();
        for (int i = 0; i < 4; i++)
        {
            int x = blocks[i].x;
            int y = blocks[i].y;

            // захист від виходу за межі
        if (y >= 0 && y < fieldHeight && x >= 0 && x < fieldWidth)
            field[y][x] = 1;
        }
    }



