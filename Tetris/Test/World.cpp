#include "World.h"
#include "Figure.h"


using namespace std;
    //****
    World::World()
    {
        needFigure = true;

        //������� ����
        for (int y = 0; y < fieldHeight; y++)
            for (int x = 0; x < fieldWidth; x++)
                field[y][x] = 0;

        //����� ������� �����
        for (int y = 0; y < fieldHeight; y++)
            for (int x = 0; x < fieldWidth; x++)
                colorField[y][x] = cyan; // ��� ����-���� ������
    }

    World::~World() {}

    bool World::getBool()
    {
        return needFigure;
    }

    int World::getScore()
    {
        return score;
    }

    bool World::getStop()
    {
        for (int x = 0; x < fieldWidth; x++)
        {
            if (field[0][x])
                return true;
        }
        return false;
    }

    void World::figureP()
    {
        needFigure = true;
    }

    void World::figureM()
    {
        needFigure = false;
    }

    ColorFigure(*World::getColorField())[fieldWidth]
    {
        return colorField;
    }

        int(*World::getField())[fieldWidth]
    {
        return field;
    }

        void World::fixFigure(const Figure* figure)
    {
        const sf::Vector2i* blocks = figure->getCord();    // ���� �����
        ColorFigure figureColor = figure->getColorEnum(); // ���� ����
        for (int i = 0; i < 4; i++)
        {
            int x = blocks[i].x;
            int y = blocks[i].y;

            // ������ �� ������ �� ���
        if (y >= 0 && y < fieldHeight && x >= 0 && x < fieldWidth)
            field[y][x] = 1;
            colorField[y][x] = figureColor;
        }

        score += 5;
    }

    void World::checkLines()
    {
        for (int y = fieldHeight - 1; y >= 0; y--)
        {
            bool full = true;
            for (int x = 0; x < fieldWidth; x++)
            {
                if (field[y][x] == 0)
                {
                    full = false;
                    break;
                }
            }

            if (full)
            {
                // ������� �� ����� ��� �������� ����
                for (int row = y; row > 0; row--)
                {
                    for (int x = 0; x < fieldWidth; x++)
                    {
                        field[row][x] = field[row - 1][x];
                    }
                }

                // ������ ����� �������
                for (int x = 0; x < fieldWidth; x++)
                {
                    field[0][x] = 0;
                }

                y++; //�������� ���� � ����� �� ���
                score += 10;
            }
        }
    }



