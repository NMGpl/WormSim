#include "Graphics.h"
#include "Button.h"
#include "Input.h"
#include "InputManager.h"
#include "Simulation.h"
#include "raylib.h"
#include "Worm.h"
#include <vector>
#include <iostream>

Graphics::Graphics(Simulation& simulation, int x, int y) {
	this->x = x;
	this->y = y;
	this->simulation = simulation;
	prepareButtons(985, 50, 170, 30);
	prepareInputs(1165, 50, 95, 30);
	generateWormBoxRandom();
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(x, y, "WormSim");
}

void Graphics::begin() const {
	BeginDrawing();
}

void Graphics::draw() {
	ClearBackground(BLACK);
	DrawText("WormSim", x / 2 - 50, 10, 20, WHITE);
	drawMenu();
	drawWormBox();
	drawWorm();
}

void Graphics::drawMenu() {
	DrawRectangleLines(10, 40, 275, y - 50, WHITE);						//Lewe menu ?????
	DrawRectangleLines(975, 40, 295, y - 50, WHITE);					//Prawe menu
	drawInputs();
	drawButtons();
}

void Graphics::prepareButtons(int startX, int startY, int width, int height) {
	Button bRegen(startX, startY, width, height, "Reg. podloza");
	buttons.push_back(bRegen);
	Button bHunger(startX, startY + 40, width, height, "Odpornosc na glod");
	buttons.push_back(bHunger);
	Button bSize(startX, startY + 80, width, height, "Maks. wielkosc");
	buttons.push_back(bSize);
	Button bLifespan(startX, startY + 120, width, height, "Sr. czas zycia");
	buttons.push_back(bLifespan);
	Button bChildren(startX, startY + 160, width, height, "Ilosc mlodych");
	buttons.push_back(bChildren);
	Button bProductivity(startX, startY + 200, width, height, "Sr. czas prod.");
	buttons.push_back(bProductivity);
	Button bGenerateRandom(985, y - 50, 132, 30, "Losowo");
	buttons.push_back(bGenerateRandom);
	Button bGenerateHotspot(985 + 143, y - 50, 132, 30, "Strefy");
	buttons.push_back(bGenerateHotspot);
	Button bAddWorm(startX, startY + 240, width, height, "Dodaj robaka");
	buttons.push_back(bAddWorm);
	Button bDeleteWorms(startX + 180, startY + 240, 95, height, "Wyczysc");
	buttons.push_back(bDeleteWorms);
}

void Graphics::prepareInputs(int startX, int startY, int width, int height) {
	for (int i = 0; i < 6; i++) {
		Input input(startX, startY, width, height, 10, i);
		inputs.push_back(input);
		startY += 40;
	}
}

void Graphics::drawButtons() {
	int i = 0;
	for (Button& button : buttons) {
		int x = button.getX();
		int y = button.getY();
		int width = button.getWidth();
		int height = button.getHeight();
		if (manager.isMouseOver(x, y, width, height)) {
			button.setColor(RED);
			if (manager.isLMouseClicked()) {
				switch (i) {
				case 0:

					break;
				case 1:

					break;
				case 2:

					break;
				case 3:

					break;
				case 4:

					break;
				case 5:

					break;
				case 6:
					generateWormBoxRandom();
					break;
				case 7:
					generateWormBoxHotspot();
					break;
				case 8:
					simulation.addWorm(1);
					break;
				case 9:
					simulation.deleteWorms();
					break;
				}
			}
		} else button.setColor(WHITE);
		i += 1;
		button.draw();
	}
}

void Graphics::drawInputs() {
	for (Input& input : inputs) {
		int x = input.getX();
		int y = input.getY();
		int value = input.getValue();
		int width = input.getWidth();
		int height = input.getHeight();
		if (manager.isMouseOver(x, y, width, height)) {
			input.setColor(RED);
			if (manager.isLMouseClicked()) {
				input.setValue(value + 1);
			}
			else if (manager.isRMouseClicked()) {
				input.setValue(value - 1);
			}
		} else input.setColor(WHITE);
		input.draw();
	}
}

void Graphics::generateWormBoxRandom() {
	this->tiles = simulation.generateBoardRandom(670, 670);
}

void Graphics::generateWormBoxHotspot() {
	this->tiles = simulation.generateBoardHotspot(670, 670, 15);
}

void Graphics::drawWormBox() const {
	drawTiles(670, 670, 10);
	DrawRectangleLines(295, 40, y - 50, y - 50, WHITE);
}

void Graphics::drawWorm() {
	for (Worm& worm : simulation.getWorms()) {
		int x = worm.getHeadX();
		int y = worm.getHeadY();
		//DrawRectangle(x, y, 5, 5, YELLOW);
		drawWorm(x, y, 6);
	}
}

void Graphics::drawWorm(int x, int y, int size) const {
	DrawRectangle(297 + x * 10, 42 + y * 10, size, size, WHITE);
}

void Graphics::drawTiles(int width, int height, int size) const {
	for (int i = 0; i < width / size; i++) {
		for (int j = 0; j < height / size; j++) {
			int tileFood = tiles[i][j];
			if (tileFood == 3) DrawRectangle(295 + (i * size), 40 + (j * size), size, size, GREEN);
			else if (tileFood == 2) DrawRectangle(295 + (i * size), 40 + (j * size), size, size, ORANGE);
			else if (tileFood == 1) DrawRectangle(295 + (i * size), 40 + (j * size), size, size, RED);
			else DrawRectangle(295 + (i * size), 40 + (j * size), size, size, BLACK);
		}
	}
}

void Graphics::end() const {
	EndDrawing();
}