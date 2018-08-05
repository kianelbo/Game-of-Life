#include <SFML/Graphics.hpp>
using namespace sf;

const int verticalSize = 24;
const int horizontalSize = 40;
const int cellSize = 40;
int width = horizontalSize * cellSize;
int height = verticalSize * cellSize;

bool curGrid[verticalSize][horizontalSize];
bool nextGrid[verticalSize][horizontalSize];

int main() {
	
	for (int i = 0; i < verticalSize; i++)
		for (int j = 0; j < horizontalSize; j++) {
			curGrid[i][j] = false;
			nextGrid[i][j] = false;
		}

	RenderWindow window(VideoMode(1920, 1440), "Conway's Game of Life", Style::Close);

	// board
	Color gray(80, 80, 85);
	RectangleShape boardBorder(Vector2f(width, height));
	boardBorder.setOutlineColor(Color::Black);
	boardBorder.setOutlineThickness(5);
	boardBorder.setFillColor(gray);
	boardBorder.setPosition(160, 160);

	// grid lines
	RectangleShape cellBorder;
	cellBorder.setFillColor(Color::Black);

	// alive cell block
	RectangleShape cell(Vector2f(cellSize - 4, cellSize - 4));
	cell.setFillColor(Color::White);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();


			// input
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
				int clickX = event.mouseButton.x;
				int clickY = event.mouseButton.y;
				if (clickX > 160 && clickX < 160 + width && clickY > 160 && clickY < 160 + height) {
					int cellX = (clickX - 160) / cellSize;
					int cellY = (clickY - 160) / cellSize;
					curGrid[cellY][cellX] = !curGrid[cellY][cellX];
				}
				
			}

	

			/*if (event.type == Event::KeyPressed) {
				if (event.KeyPressed == Keyboard::Space)
					for (int i = 0; i < verticalSize; i++)
						for (int j = 0; j < horizontalSize; j++)
							curGrid[i][j] == false;

				if (event.KeyPressed == Keyboard::Right)
					for (int i = 0; i < verticalSize; i++)
						for (int j = 0; j < horizontalSize; j++)
							curGrid[i][j] == nextGrid[i][j];
			}*/
		}

		
		// calculating the next grid
		for (int i = 0; i < horizontalSize; i++) {
			for (int j = 0; j < verticalSize; j++) {
				// get number of neighbours
				int neighbours = 0;
				if (i > 0 && curGrid[i - 1][j]) neighbours++;
				if (i < verticalSize - 1 && curGrid[i + 1][j]) neighbours++;
				if (j > 0 && curGrid[i][j - 1]) neighbours++;
				if (j < horizontalSize - 1 && curGrid[i][j + 1]) neighbours++;
				if (i > 0 && j > 0 && curGrid[i - 1][j - 1]) neighbours++;
				if (i > 0 && j < horizontalSize - 1 && curGrid[i - 1][j + 1]) neighbours++;
				if (i < verticalSize - 1 && j > 0 && curGrid[i + 1][j - 1]) neighbours++;
				if (i < verticalSize - 1 && j > horizontalSize - 1 && curGrid[i + 1][j + 1]) neighbours++;

				// rules
				if (curGrid[i][j] && (neighbours < 2 || neighbours > 3)) nextGrid[i][j] = false;
				if (curGrid[i][j] && (neighbours == 2 || neighbours == 3)) nextGrid[i][j] = true;
				if (!curGrid[i][j] && neighbours == 3) nextGrid[i][j] = true;
			}
		}




		// draw
		window.clear(Color::White);

		window.draw(boardBorder);

		// draw vertical grid lines
		for (int i = 0; i < horizontalSize; i++) {
			cellBorder.setSize(Vector2f(1, height));
			cellBorder.setPosition(160 + i * cellSize, 160);
			window.draw(cellBorder);
		}
		// draw horizontal grid lines
		for (int i = 0; i < verticalSize; i++) {
			cellBorder.setSize(Vector2f(width, 1));
			cellBorder.setPosition(160, 160 + i * cellSize);
			window.draw(cellBorder);
		}

		// draw alive cells
		for (int i = 0; i < verticalSize; i++) {
			for (int j = 0; j < horizontalSize; j++) {
				if (curGrid[i][j]) {
					cell.setPosition(162 + j * cellSize, 162 + i * cellSize);
					window.draw(cell);
				}
			}
		}

		window.display();
	}


	return 0;
}
