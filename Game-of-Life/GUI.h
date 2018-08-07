#pragma once
#include <SFML/Graphics.hpp>

#define CELL_SIZE 8
#define BUTTON_BLOCKS 4
#define BUTTON_X 808


using namespace sf;


class GUI {
private:
	RenderWindow &window;

	Font font;
	RectangleShape cells;
	Text buttonNext;
	Text buttonLock;
	Text buttonAdd;
	Text buttonClean;
	Text buttonLoadW;
	Text buttonSaveW;

	void cellsSetup();
	void buttonsSetup();
	void draw();

public:
	GUI(RenderWindow &window);

	void setupWindow();
	void setCells(int cellPositionX, int cellPositionY, int alive);
};
