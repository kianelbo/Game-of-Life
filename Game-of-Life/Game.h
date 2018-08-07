#pragma once
#include "GUI.h"
#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 850
#define ARRAY_SIZE 100

using namespace sf;

class Game {
private:
	int mouseX, mouseY;
	int cellX, cellY;
	RenderWindow window;
	GUI gui;

	int world[ARRAY_SIZE][ARRAY_SIZE];
	int neighbours[ARRAY_SIZE][ARRAY_SIZE];
	bool pause;

	void processEvents();
	void render();
	void nextGen();
	void zeroArray(int arr[][ARRAY_SIZE]);
	bool isEmptyWorld();
	void clickOnScreen(int cellPositionX, int cellPositionY);

public:
	Game();

	void run();
};
