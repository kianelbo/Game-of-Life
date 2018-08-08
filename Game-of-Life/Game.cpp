#include "Game.h"
#include <time.h>
#include <fstream>

Game::Game() : gui(window) {
	window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game of Life", Style::Titlebar | Style::Close);
	srand(time(NULL));
	pause = true;
	zeroArray(world);
}


void Game::run() {
	while (window.isOpen()) {
		processEvents();
		if (!pause) nextGen();
		render();
	}
}


void Game::render() {
	for (int i = 0; i < ARRAY_VSIZE; i++)
		for (int j = 0; j < ARRAY_HSIZE; j++)
			gui.setCells(ORIGIN_XY + CELL_SIZE * j, ORIGIN_XY + CELL_SIZE * i, world[i][j]);

	gui.setupWindow();
}


void Game::processEvents() {
	Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {

		case Event::Closed:
			window.close();
			break;


		case Event::MouseButtonPressed:

			int element = gui.getClickedElement(event.mouseButton.x, event.mouseButton.y);
			switch (element) {
			case -2:	// lock clicked
				pause = !pause;
			case -10:	// no cell nor button clicked
				break;
			case -1:	// next clicked
				if (pause) nextGen();
				break;
			case -3:	// add clicked
				if (pause)
					for (int i = 0; i < 50; i++) {
						int x = rand() % ARRAY_HSIZE;
						int y = rand() % ARRAY_VSIZE;
						while (world[y][x]) {
							x = rand() % ARRAY_HSIZE;
							y = rand() % ARRAY_VSIZE;
						}
						world[y][x] = 1;
					}
				break;
			case -4:	// clean clicked
				if (pause) zeroArray(world);
				break;
			case -5:	// load clicked
				if (pause) loadFile();
				break;
			case -6:	// save clicked
				if (pause) saveFile();
				break;
			default:	// cell clicked
				if (!pause) break;
				int cX = element / ARRAY_HSIZE;
				int cY = element % ARRAY_HSIZE;
				world[cX][cY] = !world[cX][cY];
			}
		}
	}
}


void Game::zeroArray(int arr[][ARRAY_HSIZE]) {
	for (int i = 0; i < ARRAY_VSIZE; i++)
		for (int j = 0; j < ARRAY_HSIZE; j++)
			arr[i][j] = 0;
}


void Game::nextGen() {
	zeroArray(neighbours);

	// get number of neighbours
	for (int i = 0; i < ARRAY_VSIZE; i++) {
		for (int j = 0; j < ARRAY_HSIZE; j++) {
			int nCount = 0;
			if (i > 0 && world[i - 1][j]) nCount++;
			if (i < ARRAY_VSIZE - 1 && world[i + 1][j]) nCount++;
			if (j > 0 && world[i][j - 1]) nCount++;
			if (j < ARRAY_HSIZE - 1 && world[i][j + 1]) nCount++;
			if (i > 0 && j > 0 && world[i - 1][j - 1]) nCount++;
			if (i > 0 && j < ARRAY_HSIZE - 1 && world[i - 1][j + 1]) nCount++;
			if (i < ARRAY_VSIZE - 1 && j > 0 && world[i + 1][j - 1]) nCount++;
			if (i < ARRAY_VSIZE - 1 && j < ARRAY_HSIZE - 1 && world[i + 1][j + 1]) nCount++;

			neighbours[i][j] = nCount;
		}
	}

	// applying rules
	for (int i = 0; i < ARRAY_VSIZE; i++)
		for (int j = 0; j < ARRAY_HSIZE; j++) {
			if (neighbours[i][j] == 3)
				world[i][j] = 1;

			else if (neighbours[i][j] == 2)
				world[i][j] = world[i][j];

			else
				world[i][j] = 0;
		}


	if (isEmptyWorld())
		pause = true;
}


bool Game::isEmptyWorld() {
	for (int i = 0; i < ARRAY_VSIZE; i++)
		for (int j = 0; j < ARRAY_HSIZE; j++)
			if (world[i][j] == 1) return false;

	return true;
}


void Game::loadFile() {
	std::ifstream inFile("world.save");

	for (int i = 0; i < ARRAY_VSIZE; i++)
		for (int j = 0; j < ARRAY_HSIZE; j++)
			inFile >> world[i][j];

	inFile.close();
}


void Game::saveFile() {
	std::ofstream outFile("world.save");

	for (int i = 0; i < ARRAY_VSIZE; i++)
		for (int j = 0; j < ARRAY_HSIZE; j++)
			outFile << world[i][j] << " ";

	outFile.close();
}
