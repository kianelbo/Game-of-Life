#include "GUI.h"



GUI::GUI(RenderWindow &window) : window(window) {};


void GUI::setupWindow() {
	cellsSetup();
	buttonsSetup();
	draw();
	window.display();
}


void GUI::cellsSetup() {
	Vector2f cellSize(CELL_SIZE, CELL_SIZE);
	cells.setSize(cellSize);
	cells.setOutlineColor(Color::Blue);
	cells.setOutlineThickness(0.6);
}


void GUI::buttonsSetup() {
	font.loadFromFile("LedDisplay.ttf");
	buttonNext.setFont(font);
	buttonLock.setFont(font);
	buttonAdd.setFont(font);
	buttonClean.setFont(font);
	buttonLoadW.setFont(font);
	buttonSaveW.setFont(font);

	buttonNext.setString("NEXT");
	buttonLock.setString("LOCK");
	buttonAdd.setString("ADD CELLS");
	buttonClean.setString("CLEAN WORLD");
	buttonLoadW.setString("LOAD WORLD");
	buttonSaveW.setString("SAVE WORLD");

	buttonNext.setCharacterSize(BUTTON_BLOCKS * CELL_SIZE);
	buttonLock.setCharacterSize(BUTTON_BLOCKS * CELL_SIZE);
	buttonAdd.setCharacterSize(BUTTON_BLOCKS * CELL_SIZE);
	buttonClean.setCharacterSize(BUTTON_BLOCKS * CELL_SIZE);
	buttonLoadW.setCharacterSize(BUTTON_BLOCKS * CELL_SIZE);
	buttonSaveW.setCharacterSize(BUTTON_BLOCKS * CELL_SIZE);

	buttonNext.setFillColor(Color::Green);
	buttonLock.setFillColor(Color::Green);
	buttonAdd.setFillColor(Color::Green);
	buttonClean.setFillColor(Color::Green);
	buttonLoadW.setFillColor(Color::Green);
	buttonSaveW.setFillColor(Color::Green);

	buttonNext.setPosition(BUTTON_X, 0);
	buttonLock.setPosition(BUTTON_X, BUTTON_BLOCKS*CELL_SIZE);
	buttonAdd.setPosition(BUTTON_X, 2 * BUTTON_BLOCKS*CELL_SIZE);
	buttonClean.setPosition(BUTTON_X, 3 * BUTTON_BLOCKS*CELL_SIZE);
	buttonLoadW.setPosition(BUTTON_X, 4 * BUTTON_BLOCKS*CELL_SIZE);
	buttonSaveW.setPosition(BUTTON_X, 5 * BUTTON_BLOCKS*CELL_SIZE);
}


void GUI::draw() {
	window.draw(buttonNext);
	window.draw(buttonLock);
	window.draw(buttonAdd);
	window.draw(buttonClean);
	window.draw(buttonLoadW);
	window.draw(buttonSaveW);
}


void GUI::setCells(int cellPositionX, int cellPositionY, int alive) {
	cells.setPosition(cellPositionX, cellPositionY);

	if (alive)
		cells.setFillColor(Color::White);
	else
		cells.setFillColor(Color::Black);

	window.draw(cells);
}
