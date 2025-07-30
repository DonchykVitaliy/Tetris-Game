#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <SFML/Graphics.hpp>
//classes
#include "World.h"
#include "Figure.h"
//windows
#include "deathWindow.h"
#include "infoWindow.h"

using namespace sf;
using namespace std;

World world;
Font font;
Type type = None;
Direction moveSite = No;
Clock moveClock;
const int tileSize = 50; // розмір блоку
const int offsetX = 150; // рамка зліва
const int offsetY = 0;   // верхній відступ (0 — фігура починає з самого верху)


int main()
{
	Color gray(187, 187, 187);
	font.loadFromFile("arial.ttf");

	bool ChangeSite = false;
	int weight = 800, height = 900;

	Figure* figure = nullptr;
	sf::RectangleShape blockShape(sf::Vector2f(50.f, 50.f));
	blockShape.setFillColor(sf::Color::Cyan);

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
				if (event.key.code == Keyboard::Space) {
					cout << "space";
					ChangeSite = true;
				}
			}
		}
		// фон
		window.clear(Color::Black);

		// лінії
		int LineW = weight;
		do {
			if (LineW >= 150 && LineW <= 650)
			{
				RectangleShape line(Vector2f(2.f, height - 150.f));
				line.setFillColor(Color::White);
				line.move(LineW, 0.f);
				window.draw(line);
			}
			LineW -= 50.f;
		} while (LineW);

		int LineH = height;
		do {
			RectangleShape line(Vector2f(weight - 300.f, 2.f));
			line.setFillColor(Color::White);
			line.move(150.f, LineH-150.f);
			window.draw(line);
			LineH -= 50.f;
		} while (LineH);


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
				world.fixFigure(figure);
				world.figureP();
				delete figure;
				figure = nullptr;
			}
			else {
				figure->fall();		//якщо ще не впала, то відтворюється падіння

				//buttons
				if (ChangeSite)
				{
					figure->rotate(world.getField());
					ChangeSite = false;
				}

				if (moveSite != No)
				{
					if (moveSite == Down)			//бистро до низу
						figure->fastFall(world.getField());
					else if (moveSite == Left)		//вліво
						figure->move(1);
					else
						figure->move(2);			//вправо

					//back to default
					moveSite = No;
				}
			}

			fallClock.restart();
		}


		//figure
		int(*field)[fieldWidth] = world.getField();
		for (int y = 0; y < fieldHeight; y++) {
			for (int x = 0; x < fieldWidth; x++) {
				if (field[y][x]) {
					blockShape.setPosition(offsetX + x * tileSize, offsetY + y * tileSize);
					window.draw(blockShape);
				}
			}
		}


		if (world.getBool())
		{
			if (figure) delete figure; // прибираємо стару, якщо треба
			srand(time(0));
			type = static_cast<Type>(rand() % 5);	// рандом фігура
			figure = new Figure(type);
			world.figureM();
		}

		if (figure) {
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
		scoreT.setPosition(5, height-150);
		scoreT.setFillColor(Color::White);
		window.draw(scoreT);
		// Time
		Text timerT("Time: ", font, 40);
		timerT.setPosition(350, height - 150);
		timerT.setFillColor(Color::White);
		window.draw(timerT);
		// Next figure
		Text infoT("Next figure:", font, 40);
		infoT.setPosition(weight - 230, height-150);
		infoT.setFillColor(Color::White);
		window.draw(infoT);


		


		// рендер вікна
		window.display();
	}
	return 0;
}