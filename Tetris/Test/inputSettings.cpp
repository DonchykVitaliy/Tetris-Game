#include "inputSettings.h"

int inputSettings(int& WindowW, int& WindowH)
{
    Font font;
    RenderWindow SettingsWindow(VideoMode(600, 500), "Settings", Style::Close);

    font.loadFromFile("Arial.ttf");
    Color gray(187, 187, 187);
    Color light_gray(160, 160, 160);

    bool isInput1 = true;
    bool isInput2 = false;
    int w = 0;
    int h = 0;

    //first text message
    Text mainText("In this window you can change the size of the playing\n      field. If you are satisfied with the default value,\n               press ENTER or the button below.", font, 22);
    mainText.setFillColor(Color::Black);
    mainText.setPosition(35, 15);

    //перший рядок
    Text infWeight("Weight:", font, 19);
    infWeight.setFillColor(Color::Black);
    infWeight.setPosition(270, 110);
    Text inputTextWeight("15", font, 20);
    inputTextWeight.setFillColor(Color::Black);
    inputTextWeight.setPosition(290, 148);

    string inputStringWeight = "15";
    RectangleShape inputButtonWeight(Vector2f(120, 40));
    inputButtonWeight.setPosition(240, 140);
    inputButtonWeight.setOutlineThickness(5);
    inputButtonWeight.setOutlineColor(gray);

    //другий рядок
    Text infHeight("Height:", font, 19);
    infHeight.setFillColor(Color::Black);
    infHeight.setPosition(270, 190);
    Text inputTextHeight("15", font, 20);
    inputTextHeight.setFillColor(Color::Black);
    inputTextHeight.setPosition(290, 228);

    string inputStringHeight = "15";
    RectangleShape inputButtonHeight(Vector2f(120, 40));
    inputButtonHeight.setPosition(240, 220);
    inputButtonHeight.setOutlineThickness(5);
    inputButtonHeight.setOutlineColor(gray);


    //інфо
    Text infoTitle("Info:", font, 22);
    infoTitle.setFillColor(Color::Black);
    infoTitle.setPosition(270, 400);
    Text infoText("If you enter too small values,the program\n       will use the minimum possible.", font, 22);
    infoText.setFillColor(Color::Black);
    infoText.setPosition(90, 425);

    //кнопка
    RectangleShape button(Vector2f(120, 40));
    Text buttonText("Generate", font, 22);
    buttonText.setPosition(255, 325);
    buttonText.setFillColor(Color::Black);
    button.setPosition(240, 320);
    button.setFillColor(light_gray);

    while (SettingsWindow.isOpen())
    {
        Event event;
        while (SettingsWindow.pollEvent(event))
        {
            if (event.type == Event::Closed)
                exit(0);

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePos = Mouse::getPosition(SettingsWindow);

                    // натискання на кнопку 1
                    FloatRect boundsWeight = inputButtonWeight.getGlobalBounds();
                    if (boundsWeight.contains(static_cast<Vector2f>(mousePos))) {
                        isInput1 = true;
                        isInput2 = false;
                    }

                    // натискання на кнопку 2
                    FloatRect boundsHeight = inputButtonHeight.getGlobalBounds();
                    if (boundsHeight.contains(static_cast<Vector2f>(mousePos))) {
                        isInput1 = false;
                        isInput2 = true;
                    }

                    // натискання на кнопку збереження
                    FloatRect boundsOK = button.getGlobalBounds();
                    if (boundsOK.contains(static_cast<Vector2f>(mousePos))) {
                        if (inputStringWeight != "") {
                            w = stoi(inputStringWeight);
                            if (w < 5) {
                                w = 5;
                            }
                            else if (w > 20) {
                                w = 20;
                            }
                        }
                        if (inputStringHeight != "") {
                            h = stoi(inputStringHeight);
                            if (h < 5) {
                                h = 5;
                            }
                            else if (h > 20) {
                                h = 20;
                            }
                        }
                        WindowW = w;
                        WindowH = h;
                        SettingsWindow.close();
                    }
                }
            }

            if (event.type == Event::TextEntered)
            {
                //press Enter
                if (event.text.unicode == 13 || event.text.unicode == '\n') {
                    if (inputStringWeight != "") {
                        w = stoi(inputStringWeight);
                        if (w < 5) {
                            w = 5;
                        }
                        else if (w > 20) {
                            w = 20;
                        }
                    }
                    if (inputStringHeight != "") {
                        h = stoi(inputStringHeight);
                        if (h < 5) {
                            h = 5;
                        }
                        else if (h > 20) {
                            h = 20;
                        }
                    }

                    WindowW = w;
                    WindowH = h;
                    cout << "inputStringWeight" << endl;
                    SettingsWindow.close();
                }
                if (isInput1) {
                    // введення тексту
                    if (event.text.unicode >= 48 && event.text.unicode <= 57) // дозволяємо тільки цифри (в ASCII цифри знаходяться від 48 до 57)
                    {
                        // ліміт в 4 числа
                        if (inputStringWeight.size() < 2)
                        {
                            inputStringWeight += static_cast<char>(event.text.unicode);
                            inputTextWeight.setString(inputStringWeight);
                        }
                    }
                }
                if (isInput2) {
                    // введення тексту №2
                    if (event.text.unicode >= 48 && event.text.unicode <= 57)
                    {
                        if (inputStringHeight.size() < 2)
                        {
                            inputStringHeight += static_cast<char>(event.text.unicode);
                            inputTextHeight.setString(inputStringHeight);
                        }
                    }
                }
            }

            if (event.type == Event::KeyPressed)
            {
                if (isInput1) {
                    //Backspace
                    if (event.key.code == Keyboard::BackSpace && !inputStringWeight.empty())
                    {
                        inputStringWeight.pop_back();
                        inputTextWeight.setString(inputStringWeight);
                    }
                }
                if (isInput2) {
                    //Backspace #2
                    if (event.key.code == Keyboard::BackSpace && !inputStringHeight.empty())
                    {
                        inputStringHeight.pop_back();
                        inputTextHeight.setString(inputStringHeight);
                    }
                }
            }
        }

        SettingsWindow.clear(Color::White);
        SettingsWindow.draw(mainText);
        SettingsWindow.draw(infWeight);
        SettingsWindow.draw(infHeight);
        SettingsWindow.draw(inputButtonWeight);
        SettingsWindow.draw(inputButtonHeight);
        SettingsWindow.draw(inputTextWeight);
        SettingsWindow.draw(inputTextHeight);
        SettingsWindow.draw(button);
        SettingsWindow.draw(buttonText);
        SettingsWindow.draw(infoTitle);
        SettingsWindow.draw(infoText);
        SettingsWindow.display();
    }
}