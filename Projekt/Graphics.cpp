#include "Graphics.h"
#include "Button.h"
#include "Input.h"
#include "InputManager.h"
#include "Simulation.h"
#include "raylib.h"
#include "Worm.h"
#include "Egg.h"
#include <vector>
#include <iostream>

Graphics::Graphics(Simulation& simulation, int x, int y) : simulation(simulation), tiles(simulation.getTilesRef()), config(simulation.getConfigRef()) {
	this->x = x;
	this->y = y;
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
	drawEgg();
}

void Graphics::drawMenu() {
	DrawRectangleLines(10, 40, 275, y - 50, WHITE);						//Lewe menu ?????
	DrawRectangleLines(975, 40, 295, y - 50, WHITE);					//Prawe menu
	drawInputs();
	drawButtons();
	drawInfo();
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
	Button bSimStop(startX, startY + 280, height, height, "0");
	buttons.push_back(bSimStop);
	Button bSimSpeed1(startX + height + 10, startY + 280, height, height, ">");
	buttons.push_back(bSimSpeed1);
	Button bSimSpeed2(startX + 2 * height + 20, startY + 280, height, height, ">>");
	buttons.push_back(bSimSpeed2);
	Button bSimSpeed3(startX + 3 * height + 30, startY + 280, height, height, ">>>");
	buttons.push_back(bSimSpeed3);
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
		int value;
		if (manager.isMouseOver(x, y, width, height)) {
			button.setColor(RED);
			if (manager.isLMouseClicked()) {
				switch (i) {
				case 0:
					//Food regen
					value = inputs[0].getValue();
					config.setRegenSpeed(value);
					break;
				case 1:
					value = inputs[1].getValue();
					config.setMaxHunger(value);
					break;
				case 2:
					value = inputs[2].getValue();
					config.setMaxSize(value);
					break;
				case 3:
					value = inputs[3].getValue();
					config.setMaxAge(value);
					break;
				case 4:
					value = inputs[4].getValue();
					config.setNewWormsAmount(value);
					break;
				case 5:
					value = inputs[5].getValue();
					config.setMaxProductivity(value);
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
					simulation.deleteEggs();
					break;
				case 10:
					simulation.setTickTime(0);
					break;
				case 11:
					simulation.setTickTime(1);
					break;
				case 12:
					simulation.setTickTime(5);
					break;
				case 13:
					simulation.setTickTime(10);
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
			if (manager.isLShiftClicked() && manager.isLMouseClicked()){
				input.setValue(value + 10);
			}
			else if (manager.isLMouseClicked()) {
				input.setValue(value + 1);
			}
			if (manager.isLShiftClicked() && manager.isRMouseClicked()) {
				if (value - 10 < 0) {
					input.setValue(0);
				} 
				else {
					input.setValue(value - 10);
				}
			}
			else if (manager.isRMouseClicked()) {
				if (value - 1 < 0) {
					input.setValue(0);
				}
				else {
					input.setValue(value - 1);
				}
			}
		} else input.setColor(WHITE);
		input.draw();
	}
}

void Graphics::drawInfo() {
	//DrawRectangleLines(975, 40, 295, y - 50, WHITE);					//Prawe menu
	DrawRectangleLines(985, 400, 275, 260, WHITE);

	DrawText("Ilosc robakow: ", 990, 405, 15, WHITE);
	std::string val = std::to_string(simulation.getWorms().size());
	DrawText(val.c_str(), 1200, 405, 15, WHITE);

	DrawText("Regeneracja podloza: ", 990, 405 + 15, 15, WHITE);
	val = std::to_string(config.getRegenSpeed());
	DrawText(val.c_str(), 1200, 405 + 15, 15, WHITE);

	DrawText("Odpornosc na glod: ", 990, 405 + 30, 15, WHITE);
	val = std::to_string(config.getMaxHunger());
	DrawText(val.c_str(), 1200, 405 + 30, 15, WHITE);

	DrawText("Maksymalna wielkosc: ", 990, 405 + 45, 15, WHITE);
	val = std::to_string(config.getMaxSize());
	DrawText(val.c_str(), 1200, 405 + 45, 15, WHITE);

	DrawText("Sredni czas zycia: ", 990, 405 + 60, 15, WHITE);
	val = std::to_string(config.getMaxAge());
	DrawText(val.c_str(), 1200, 405 + 60, 15, WHITE);

	DrawText("Ilosc mlodych: ", 990, 405 + 75, 15, WHITE);
	val = std::to_string(config.getNewWormsAmount());
	DrawText(val.c_str(), 1200, 405 + 75, 15, WHITE);

	DrawText("Sr. cz. produktywnosci: ", 990, 405 + 90, 15, WHITE);
	val = std::to_string(config.getMaxProductivity());
	DrawText(val.c_str(), 1200, 405 + 90, 15, WHITE);
}

void Graphics::generateWormBoxRandom() {
	simulation.generateBoardRandom(670, 670);
}

void Graphics::generateWormBoxHotspot() {
	simulation.generateBoardHotspot(670, 670, 15);
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
		
		std::vector <std::vector <int>> segments = worm.getSegments();
		if(!segments.empty()){
			for(std::vector <int> segment : segments){
				drawWorm(segment[0], segment[1], 10);
			}
		}
		
		drawWorm(x, y, 10);
		drawWormPath(worm);
	}
}

void Graphics::drawEgg() {
	for (Egg& egg : simulation.getEggs()) {
		int x = egg.getX();
		int y = egg.getY();
		//DrawRectangle(x, y, 5, 5, YELLOW);
		drawEgg(x, y, 10);
	}
}

void Graphics::drawWorm(int x, int y, int size) const {
	DrawRectangle(295 + x * 10, 40 + y * 10, size, size, WHITE);
}

void Graphics::drawEgg(int x, int y, int size) const {
	DrawRectangle(295 + x * 10, 40 + y * 10, size, size, PINK);
}

void Graphics::drawWormPath(Worm& worm) {
	std::vector <std::vector <int>> availableTiles;
	if (!worm.getMovement().empty()) {
		availableTiles = worm.getMovement();
	}
	DrawRectangleLines(295 + worm.getHeadX() * 10, 40 + worm.getHeadY() * 10, 10, 10, BLUE);
	for (int i = 0; i < availableTiles.size(); i++) {
		if (!availableTiles[i].empty()) {
			DrawRectangleLines(295 + availableTiles[i][0] * 10, 40 + availableTiles[i][1] * 10, 10, 10, PINK);
		}
	}
}

void Graphics::drawTiles(int width, int height, int size) const {
	for (int i = 0; i < width / size; i++) {
		for (int j = 0; j < height / size; j++) {
			int tileFood = tiles[i][j].getFoodAmount();
			if (tileFood == 3) DrawRectangle(295 + (i * size), 40 + (j * size), size, size, GREEN);
			else if (tileFood == 2) DrawRectangle(295 + (i * size), 40 + (j * size), size, size, ORANGE);
			else if (tileFood == 1) DrawRectangle(295 + (i * size), 40 + (j * size), size, size, RED);
			//else DrawRectangle(295 + (i * size), 40 + (j * size), size, size, BLACK);
			if (!tiles[i][j].isFree()) DrawRectangle(293 + (i * size), 38 + (j * size), 14, 14, BROWN);
		}
	}
}

void Graphics::end() const {
	EndDrawing();
}