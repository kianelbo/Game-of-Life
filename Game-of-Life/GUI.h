#pragma once
#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1440
#define ARRAY_HSIZE 80
#define ARRAY_VSIZE 50
#define ORIGIN_XY 160
#define CELL_SIZE 20
#define BUTTON_BLOCKS 6
#define BUTTON_Y 1260	// ORIGIN_XY + CELL_SIZE * ARRAY_VSIZE + 100


using namespace sf;


class GUI {
private:
	RenderWindow &window;

	Texture texture;
	RectangleShape cells;
	Sprite buttonNext;
	Sprite buttonLock;
	Sprite buttonAdd;
	Sprite buttonClean;
	Sprite buttonLoadW;
	Sprite buttonSaveW;

	void setup();
	void draw();

public:
	GUI(RenderWindow &window);

	void setupWindow();
	void setCells(int cellPositionX, int cellPositionY, int alive);
	int getClickedElement(int x, int y);
};
