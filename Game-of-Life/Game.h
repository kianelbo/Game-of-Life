#pragma once
#include "GUI.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Game {
private:
	RenderWindow window;
	GUI gui;

	char world[ARRAY_VSIZE][ARRAY_HSIZE];
	char neighbours[ARRAY_VSIZE][ARRAY_HSIZE];
	bool pause;

	void processEvents();
	void render();
	void nextGen();
	void zeroArray(char arr[][ARRAY_HSIZE]);
	bool isEmptyWorld();

	void loadFile();
	void saveFile();

public:
	Game();

	void run();
};
