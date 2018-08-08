#include "GUI.h"

Color GRAY(80, 80, 85);


GUI::GUI(RenderWindow &window) : window(window) {};


void GUI::setupWindow() {
	setup();
	draw();
	window.display();
}


void GUI::setup() {
	// cells
	Vector2f cellSize(CELL_SIZE, CELL_SIZE);
	cells.setSize(cellSize);
	cells.setOutlineColor(Color::Black);
	cells.setOutlineThickness(2);

	// buttons
	texture.loadFromFile("buttons.jpg");
	buttonNext.setTexture(texture);
	buttonLock.setTexture(texture);
	buttonAdd.setTexture(texture);
	buttonClean.setTexture(texture);
	buttonLoadW.setTexture(texture);
	buttonSaveW.setTexture(texture);

	buttonNext.setTextureRect(IntRect(0, 0, 240, 40));
	buttonLock.setTextureRect(IntRect(0, 40, 240, 40));
	buttonAdd.setTextureRect(IntRect(0, 80, 240, 40));
	buttonClean.setTextureRect(IntRect(0, 120, 240, 40));
	buttonLoadW.setTextureRect(IntRect(0, 160, 240, 40));
	buttonSaveW.setTextureRect(IntRect(0, 200, 240, 40));

	buttonNext.setPosition(440, BUTTON_Y);
	buttonLock.setPosition(440, BUTTON_Y + 60);
	buttonAdd.setPosition(840, BUTTON_Y);
	buttonClean.setPosition(840, BUTTON_Y + 60);
	buttonLoadW.setPosition(1240, BUTTON_Y);
	buttonSaveW.setPosition(1240, BUTTON_Y + 60);
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
		cells.setFillColor(GRAY);

	window.draw(cells);
}


int GUI::getClickedElement(int x, int y) {
	if (x >= ORIGIN_XY && x <= ORIGIN_XY + ARRAY_HSIZE * CELL_SIZE && y >= ORIGIN_XY && y <= ORIGIN_XY + ARRAY_VSIZE * CELL_SIZE)
		return ((y - ORIGIN_XY) / CELL_SIZE) * ARRAY_HSIZE + (x - ORIGIN_XY) / CELL_SIZE;
	else if (buttonNext.getGlobalBounds().contains(x, y))
		return -1;
	else if (buttonLock.getGlobalBounds().contains(x, y))
		return -2;
	else if (buttonAdd.getGlobalBounds().contains(x, y))
		return -3;
	else if (buttonClean.getGlobalBounds().contains(x, y))
		return -4;
	else if (buttonLoadW.getGlobalBounds().contains(x, y))
		return -5;
	else if (buttonSaveW.getGlobalBounds().contains(x, y))
		return -6;
	else
		return -10;
}

