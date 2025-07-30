#include "Figure.h"
#include "World.h"

using namespace std;

    Figure::Figure(Type type)
    {
        this->type = type;          // зберігаємо тип
        generateType(type);
    }

    Figure::~Figure()
    {
    }

    int Figure::getType()
    {
        return type;
    }

    

    //генерування випадкової форми фігури
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

    void Figure::move(int s)
    {
        bool good = true;
        if (s == 1)
        {
            //перевірка координат, чи не виходить за межі фігура
            for (int i = 0; i < 4; i++) {
                if (blocks[i].x < 1)
                    good = false;
            }

            //якщо виходить за межі, то ігнорується рух
            if (!good)
                return;

            //переміщення всієї фігури
            for (int i = 0; i < 4; i++) {
                blocks[i].x -= 1;
            }
        }
        else
        {
            //перевірка координат, чи не виходить за межі фігура
            for (int i = 0; i < 4; i++) {
                if (blocks[i].x > 8)
                    good = false;
            }

            //якщо виходить за межі, то ігнорується рух
            if (!good)
                return;

            //переміщення всієї фігури
            for (int i = 0; i < 4; i++) {
                blocks[i].x += 1;
            }
        }
    }


    //падіння фігури
    void Figure::fall()
    {
        for (int i = 0; i < 4; i++) {
            blocks[i].y += 1;
        }
    }

    void Figure::fastFall(int field[fieldHeight][fieldWidth])
    {
        bool good = true;

        while (good)
        {

            //перевірка координат, чи не виходить за межі фігура
            for (int i = 0; i < 4; i++) {
                int y_cord = (blocks[i].y) + 1;
                int x_cord = blocks[i].x;

                if (y_cord >= fieldHeight || field[y_cord][x_cord] != 0)
                {
                    good = false;
                }
            }

            //якщо виходить за межі, то ігнорується рух
            if (!good)
                break;

            //переміщення всієї фігури
            for (int i = 0; i < 4; i++) {
                blocks[i].y += 1;
            }
        }
    }

    void Figure::rotate(int field[fieldHeight][fieldWidth])
    {
        if (type == two)        //якщо це квадрат, то пропуск
            return;

        sf::Vector2f center(0.f, 0.f);  //бере центр фігури
        for (int i = 0; i < 4; i++) {
            center.x += blocks[i].x;
            center.y += blocks[i].y;
        }
        center.x /= 4.f;
        center.y /= 4.f;

        //допоміжна змінна
        sf::Vector2i temp[4];

        //get cord
        for (int i = 0; i < 4; i++)
        {
            int relX = blocks[i].x - static_cast<int>(round(center.x));
            int relY = blocks[i].y - static_cast<int>(round(center.y));

            // обертаємо за годинниковою
            temp[i].x = static_cast<int>(round(center.x)) - relY;
            temp[i].y = static_cast<int>(round(center.y)) + relX;
        }

        //перевірка на межі поля + зіткнення
        for (int i = 0; i < 4; i++) {
            int x = temp[i].x;
            int y = temp[i].y;

            if (x < 0 || x >= fieldWidth || y < 0 || y >= fieldHeight)
                return; //не
            if (field[y][x])
                return; //не
        }

        //поворот
        for (int i = 0; i < 4; i++)
            blocks[i] = temp[i];
    }

    //взяття координат
    const sf::Vector2i* Figure::getCord() const
    {
        return blocks;
    }
