#include "infoWindow.h"

int infoWindow()
{
    RenderWindow window(VideoMode(600, 500), "Info");
    Font font;
    font.loadFromFile("arial.ttf");

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
        }

        //інфо
        Text infoTitle("Info:", font, 22);
        infoTitle.setFillColor(Color::Black);
        infoTitle.setPosition(270, 600);
        Text infoText("If you enter too small values,the program\n       will use the minimum possible.", font, 22);
        infoText.setFillColor(Color::Black);
        infoText.setPosition(90, 625);
        window.draw(infoTitle);

        window.clear(Color::White);
        window.display();
    }
    return 1;
}