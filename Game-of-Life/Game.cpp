#include "Game.h"
#include <time.h>


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
	for (int i = 0; i < ARRAY_SIZE; i++)
		for (int j = 0; j < ARRAY_SIZE; j++)
			gui.setCells(8 * j, 8 * i, world[i][j]);

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
			mouseX = event.mouseButton.x;
			mouseY = event.mouseButton.y;
			cellX = mouseX / 8;
			cellY = mouseY / 8;

			clickOnScreen(cellX, cellY);
			break;
		}
	}
}


void Game::zeroArray(int arr[][ARRAY_SIZE]) {
	for (int i = 0; i < ARRAY_SIZE; i++)
		for (int j = 0; j < ARRAY_SIZE; j++)
			arr[i][j] = 0;
}


void Game::nextGen() {
	zeroArray(neighbours);

	// get number of nCount
	for (int i = 0; i < ARRAY_SIZE; i++) {
		for (int j = 0; j < ARRAY_SIZE; j++) {
			int nCount = 0;
			if (i > 0 && world[i - 1][j]) nCount++;
			if (i < ARRAY_SIZE - 1 && world[i + 1][j]) nCount++;
			if (j > 0 && world[i][j - 1]) nCount++;
			if (j < ARRAY_SIZE - 1 && world[i][j + 1]) nCount++;
			if (i > 0 && j > 0 && world[i - 1][j - 1]) nCount++;
			if (i > 0 && j < ARRAY_SIZE - 1 && world[i - 1][j + 1]) nCount++;
			if (i < ARRAY_SIZE - 1 && j > 0 && world[i + 1][j - 1]) nCount++;
			if (i < ARRAY_SIZE - 1 && j < ARRAY_SIZE - 1 && world[i + 1][j + 1]) nCount++;

			neighbours[i][j] = nCount;
		}
	}

	// applying rules
	for (int i = 0; i < ARRAY_SIZE; i++)
		for (int j = 0; j < ARRAY_SIZE; j++) {
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
	for (int i = 0; i < ARRAY_SIZE; i++)
		for (int j = 0; j < ARRAY_SIZE; j++)
			if (world[i][j] == 1) return false;

	return true;
}


void Game::clickOnScreen(int cellPositionX, int cellPositionY) {
	// cell clicked
	if (pause && cellPositionX < ARRAY_SIZE && cellPositionY < ARRAY_SIZE)
		world[cellPositionY][cellPositionX] = !world[cellPositionY][cellPositionX];

	// next clicked
	if (pause && cellPositionY <= BUTTON_BLOCKS)
		nextGen();

	// start clicked
	if (cellPositionY > BUTTON_BLOCKS && cellPositionY <= 2 * BUTTON_BLOCKS) {
		pause = !pause;
	}

	// add clicked
	if (pause && cellPositionY > 2 * BUTTON_BLOCKS && cellPositionY <= 3 * BUTTON_BLOCKS)
		for (int i = 0; i < 50; i++) {
			int x = rand() % ARRAY_SIZE;
			int y = rand() % ARRAY_SIZE;
			while (world[x][y]) {
				x = rand() % ARRAY_SIZE;
				y = rand() % ARRAY_SIZE;
			}
			world[x][y] = 1;
		}

	// clean clicked
	if (pause && cellPositionY > 3 * BUTTON_BLOCKS && cellPositionY <= 4 * BUTTON_BLOCKS)
		zeroArray(world);
}
