#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//classes
#include "World.h"
#include "Figure.h"
//windows
#include "deathWindow.h"

sf::Color getSFMLColor(ColorFigure c);
void setLines(int weight, int height, RenderWindow *window);

using namespace sf;
using namespace std;

World world;			 //базовий клас
Font font;				 //шрифт для тексту
ColorFigure color;		 //колір фігури
Type type = None;		 //тип фігури
Direction moveSite = No; //переміщення фігури в боки та низ
Clock moveClock;		 //таймер для падіння
bool stopGame = false;	 //кінець гри
const int tileSize = 50; //розмір блоку
const int offsetX = 150; //рамка зліва
const int offsetY = 0;   //верхній відступ




int main()
{
	Color gray(187, 187, 187);
	font.loadFromFile("arial.ttf");

	//sounds
	SoundBuffer bufferDown;
	bufferDown.loadFromFile("down.wav");
	Sound down;
	down.setBuffer(bufferDown);
	SoundBuffer bufferRotate;
	bufferRotate.loadFromFile("rotate.wav");
	Sound rotate;
	rotate.setBuffer(bufferRotate);

	bool ChangeSite = false;
	int weight = 800, height = 900;

	Figure* figure = nullptr;
	RectangleShape blockShape(Vector2f(50.f, 50.f));

	srand(static_cast<unsigned>(time(0)));
	RenderWindow window(VideoMode(weight, height), "Tetris");

	// якщо відкрите вікно
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// перевірка для закриття вікна
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape) {
					window.close();
				}
			}

			//управління фігурами
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Down) {
					cout << "down";
					moveSite = Down;
				}
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Right) {
					cout << "right";
					moveSite = Right;
				}
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Left) {
					cout << "left";
					moveSite = Left;
				}
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Space || event.key.code == Keyboard::Up) {
					cout << "space";
					ChangeSite = true;
				}
			}
		}
		// фон
		window.clear(Color::Black);

		// лінії
		setLines(weight, height, &window);


		//buttons
		if (ChangeSite)
		{
			figure->rotate(world.getField());
			ChangeSite = false;
			rotate.play();
		}
		if (moveSite != No)
		{
			if (moveSite == Down)			//бистро до низу
				figure->fastFall(world.getField());
			else if (moveSite == Left)		//вліво
				figure->move(1,world.getField());
			else
				figure->move(2, world.getField());			//вправо

			//back to default
			moveSite = No;
		}


		//stop game
		if (stopGame)
			deathWindow(world.getScore());


		//time
		static Clock fallClock;
		if (fallClock.getElapsedTime().asSeconds() > 0.6f && figure) {
			bool stop = false;
			//тимчасова перевірка зіткнення фігур та низу
			for (int i = 0; i < 4; i++) {
				int y = figure->getCord()[i].y;
				int x = figure->getCord()[i].x;
				if (y >= fieldHeight - 1 || world.getField()[y + 1][x]) {
					stop = true;
					break;
				}
			}


			if (stop) {		//якщо фігура досягла низу, то вона фіксується + видаляється обєкт
				stopGame = world.getStop();
				world.fixFigure(figure);
				world.checkLines();
				world.figureP();
				delete figure;
				figure = nullptr;
				down.play();
			}
			else {
				figure->fall();		//якщо ще не впала, то відтворюється падіння
			}

			fallClock.restart();
		}


		//figure
		int(*field)[fieldWidth] = world.getField();					//корди
		ColorFigure(*colors)[fieldWidth] = world.getColorField(); //колір

		for (int y = 0; y < fieldHeight; y++) {
			for (int x = 0; x < fieldWidth; x++) {
				if (field[y][x]) {
					blockShape.setFillColor(getSFMLColor(colors[y][x]));
					blockShape.setPosition(offsetX + x * tileSize, offsetY + y * tileSize);
					window.draw(blockShape);
				}
			}
		}


		if (world.getBool())		//перевірка чи треба нова фігура
		{
			if (figure) delete figure; // прибираємо стару, якщо треба
			type = static_cast<Type>(rand() % 5);	// рандом фігура
			color = static_cast<ColorFigure>(rand() % 5);	// рандом фігура
			figure = new Figure(type, color);
			world.figureM();
		}

		//якщо створена нова фігура, то її налаштовує
		if (figure) {
			blockShape.setFillColor(figure->getColor());
			const sf::Vector2i* cords = figure->getCord();
			for (int i = 0; i < 4; i++) {
				int x = cords[i].x;
				int y = cords[i].y;

				blockShape.setPosition(offsetX + x * tileSize, offsetY + y * tileSize);
				window.draw(blockShape);
			}
		}



		// Score
		Text scoreT("Score: ", font, 40);
		scoreT.setPosition(5.f, height-150.f);
		scoreT.setFillColor(Color::White);
		window.draw(scoreT);

		Text score(to_string(world.getScore()), font, 40.f);
		score.setPosition(5.f, height - 100.f);
		score.setFillColor(Color::White);
		window.draw(score);
		// Time
		Text timerT("Time: ", font, 40.f);
		timerT.setPosition(350.f, height - 150.f);
		timerT.setFillColor(Color::White);
		window.draw(timerT);
		// Next figure
		Text infoT("Next figure:", font, 40.f);
		infoT.setPosition(weight - 230.f, height-150.f);
		infoT.setFillColor(Color::White);
		window.draw(infoT);


		// рендер вікна
		window.display();
	}
	return 0;
}


//колір для фігури
sf::Color getSFMLColor(ColorFigure c)
{
	switch (c)
	{
	case red: return sf::Color::Red;
	case blue: return sf::Color::Blue;
	case green: return sf::Color::Green;
	case yellow: return sf::Color::Yellow;
	case purple: return sf::Color(128, 0, 128);
	case cyan: return sf::Color::Cyan;
	default: return sf::Color::White;
	}
}


//візуалізація клітинок
void setLines(int weight, int height, RenderWindow* window)
{
	int LineW = weight;
	do {
		if (LineW >= 150 && LineW <= 650)
		{
			RectangleShape line(Vector2f(2.f, height - 150.f));
			line.setFillColor(Color::White);
			line.move(LineW, 0.f);
			window->draw(line);
		}
		LineW -= 50.f;
	} while (LineW);

	int LineH = height;
	do {
		RectangleShape line(Vector2f(weight - 300.f, 2.f));
		line.setFillColor(Color::White);
		line.move(150.f, LineH - 150.f);
		window->draw(line);
		LineH -= 50.f;
	} while (LineH);
}