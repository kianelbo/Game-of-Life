#pragma once
#include "GUI.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Game {
private:
	RenderWindow window;
	GUI gui;

	int world[ARRAY_VSIZE][ARRAY_HSIZE];
	int neighbours[ARRAY_VSIZE][ARRAY_HSIZE];
	bool pause;

	void processEvents();
	void render();
	void nextGen();
	void zeroArray(int arr[][ARRAY_HSIZE]);
	bool isEmptyWorld();

	void loadFile();
	void saveFile();

public:
	Game();

	void run();
};
