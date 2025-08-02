#include "Figure.h"
#include "World.h"

using namespace std;

    Figure::Figure(Type type, ColorFigure color)
    {
        this->color = color;
        this->type = type;
        generateType(type);
    }

    Figure::~Figure()
    {
    }

    int Figure::getType()
    {
        return type;
    }

    

    //����������� ��������� ����� ������
    void Figure::generateType(Type t)
    {
        switch (t)
        {
        case one:   // I
            blocks[0] = { 3, 0 };
            blocks[1] = { 4, 0 };
            blocks[2] = { 5, 0 };
            blocks[3] = { 6, 0 };
            break;
        case two:   // O
            blocks[0] = { 4, 0 };
            blocks[1] = { 5, 0 };
            blocks[2] = { 4, 1 };
            blocks[3] = { 5, 1 };
            break;
        case three: // L
            blocks[0] = { 3, 0 };
            blocks[1] = { 4, 0 };
            blocks[2] = { 5, 0 };
            blocks[3] = { 5, 1 };
            break;
        case four:  // Z
            blocks[0] = { 3, 0 };
            blocks[1] = { 4, 0 };
            blocks[2] = { 4, 1 };
            blocks[3] = { 5, 1 };
            break;
        case five:  // T
            blocks[0] = { 3, 0 };
            blocks[1] = { 4, 0 };
            blocks[2] = { 5, 0 };
            blocks[3] = { 4, 1 };
            break;
        default:
            break;
        }
    }


    //���������� ������ �� ����
    void Figure::move(int s,int field[fieldHeight][fieldWidth])
    {
        bool good = true;
        if (s == 1)
        {
            //�������� ���������, �� �� �������� �� ��� ������ �� ���� �������� ����
            for (int i = 0; i < 4; i++) {
                if (blocks[i].x < 1 || field[blocks[i].y][blocks[i].x-1])
                    good = false;
            }

            //���� �������� �� ���, �� ���������� ���
            if (!good)
                return;

            //���������� �񳺿 ������
            for (int i = 0; i < 4; i++) {
                blocks[i].x -= 1;
            }
        }
        else
        {
            //�������� ���������, �� �� �������� �� ��� ������ �� ���� �������� ������
            for (int i = 0; i < 4; i++) {
                if (blocks[i].x > 8 || field[blocks[i].y][blocks[i].x + 1])
                    good = false;
            }

            //���� �������� �� ���, �� ���������� ���
            if (!good)
                return;

            //���������� �񳺿 ������
            for (int i = 0; i < 4; i++) {
                blocks[i].x += 1;
            }
        }
    }


    //������ ������
    void Figure::fall()
    {
        for (int i = 0; i < 4; i++) {
            blocks[i].y += 1;
        }
    }


    //������ ������
    void Figure::fastFall(int field[fieldHeight][fieldWidth])
    {
        bool good = true;

        while (good)
        {

            //�������� ���������, �� �� �������� �� ��� ������
            for (int i = 0; i < 4; i++) {
                int y_cord = (blocks[i].y) + 1;
                int x_cord = blocks[i].x;

                if (y_cord >= fieldHeight || field[y_cord][x_cord] != 0)
                {
                    good = false;
                }
            }

            //���� �������� �� ���, �� ���������� ���
            if (!good)
                break;

            //���������� �񳺿 ������
            for (int i = 0; i < 4; i++) {
                blocks[i].y += 1;
            }
        }
    }


    //������� ������
    void Figure::rotate(int field[fieldHeight][fieldWidth])
    {
        if (type == two)        //���� �� �������, �� �������
            return;

        sf::Vector2f center(0.f, 0.f);  //���� ����� ������
        for (int i = 0; i < 4; i++) {
            center.x += blocks[i].x;
            center.y += blocks[i].y;
        }
        center.x /= 4.f;
        center.y /= 4.f;

        //�������� �����
        sf::Vector2i temp[4];

        //get cord
        for (int i = 0; i < 4; i++)
        {
            int relX = blocks[i].x - static_cast<int>(round(center.x));
            int relY = blocks[i].y - static_cast<int>(round(center.y));

            // �������� �� ������������
            temp[i].x = static_cast<int>(round(center.x)) - relY;
            temp[i].y = static_cast<int>(round(center.y)) + relX;
        }

        //�������� �� ��� ���� + ��������
        for (int i = 0; i < 4; i++) {
            int x = temp[i].x;
            int y = temp[i].y;

            if (x < 0 || x >= fieldWidth || y < 0 || y >= fieldHeight)
                return; //��
            if (field[y][x])
                return; //��
        }

        //�������
        for (int i = 0; i < 4; i++)
            blocks[i] = temp[i];
    }

    //������ ���������
    const sf::Vector2i* Figure::getCord() const
    {
        return blocks;
    }


    //����
    sf::Color Figure::getColor() const
    {
        switch (color)
        {
        case red:
            return sf::Color::Red;
        case blue:
            return sf::Color::Blue;
        case green:
            return sf::Color::Green;
        case yellow:
            return sf::Color::Yellow;
        case purple:
            return sf::Color(128, 0, 128); // ���������
        case cyan:
            return sf::Color::Cyan;
        default:
            return sf::Color::White;
        }
    }

    ColorFigure Figure::getColorEnum() const
    {
        return color;
    }