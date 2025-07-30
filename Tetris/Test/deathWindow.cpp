#include "deathWindow.h"
#include "Figure.h"

int deathWindow(int s)
{
    Font font;
    RenderWindow window(VideoMode(500, 500), "Scoreboard");
    font.loadFromFile("arial.ttf");
    Color gray(187, 187, 187);
    Color light_gray(160, 160, 160);
    int Score = 0;
    string stScore = "";
    bool add = false;

    //// file score
    ifstream checkFile("score.txt");
    if (checkFile.good()) {}
    else {                                    // if file not found
        checkFile.close();
        ofstream createFile("score.txt");
        if (createFile.is_open()) {}          // create file
        else cout << "file not found/created!" << endl;
        createFile.close();
    }

    ifstream file("score.txt");
    if (file.peek() == std::ifstream::traits_type::eof()) {           // test if file empty
        cout << "file empty" << endl;
        add = true;
        Score = s;
    }
    else {
        getline(file, stScore);         // copy text from file to stScore
        Score = stoi(stScore);          // convert to int
        if (Score < s) {                // if file score < score in last game then replace number in file
            Score = s;
            add = true;
        }
    }
    file.close();

    if (add)                            // replace number in file
    {
        ofstream fileAdd("score.txt");
        cout << "add " << Score;
        fileAdd << Score;
        add = false;
        fileAdd.close();
    }


        //текст очків
        Text score("Total Score:", font, 35);
        score.setFillColor(Color::Black);
        score.setPosition(170, 20);
        Text outScore(to_string(s), font, 35);
        outScore.setFillColor(Color::Black);
        outScore.setPosition(250, 55);

        //текст очків
        Text bestScore("Best Score:", font, 35);
        bestScore.setFillColor(Color::Black);
        bestScore.setPosition(170, 105);
        Text outBestScore(to_string(Score), font, 35);
        outBestScore.setFillColor(Color::Black);
        outBestScore.setPosition(250, 140);

        //текст підбадрювання
        Text text("You lost, but you can start the game\n       again and get a better result!", font, 25);
        text.setFillColor(Color::Black);
        text.setPosition(50, 390);

        //кнопка
        RectangleShape button(Vector2f(150, 50));
        Text buttonText("Close", font, 35);
        buttonText.setPosition(210, 312);
        buttonText.setFillColor(Color::Black);
        button.setPosition(180, 310);
        button.setFillColor(light_gray);

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    exit(0);

                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Escape || event.key.code == Keyboard::Enter) {
                        exit(0);
                    }
                }

                if (event.type == Event::MouseButtonPressed) {
                    if (event.mouseButton.button == Mouse::Left) {
                        Vector2i mousePos = Mouse::getPosition(window);

                        // натискання на кнопку
                        FloatRect closeButton = button.getGlobalBounds();
                        if (closeButton.contains(static_cast<Vector2f>(mousePos))) {
                            exit(0);
                        }
                    }
                }
            }

        window.clear(Color::White);
        window.draw(score);
        window.draw(text);
        window.draw(outScore);
        window.draw(bestScore);
        window.draw(outBestScore);
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }
        return 1;
}