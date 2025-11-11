#include "Graphics.h"
#include "Button.h"
#include "Input.h"
#include "InputManager.h"
#include "raylib.h"
#include <vector>
#include <iostream>

Graphics::Graphics(int x, int y) {
	this->x = x;
	this->y = y;
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(x, y, "WormSim");
}

void Graphics::begin() const {
	BeginDrawing();
}

void Graphics::draw() const {
	ClearBackground(BLACK);
	DrawText("WormSim", x / 2 - 50, 10, 20, WHITE);
	//int i = MeasureText("Siz", 20);
	//DrawRectangleLines(10, 40, x - 20, y - 50, WHITE); //width = 1260; height = 670
	drawMenu();
	drawWormBox();
	//std::cout << i;
}

void Graphics::drawMenu() const {
	DrawRectangleLines(10, 40, 275, y - 50, WHITE);						//Lewe menu ?????
	DrawRectangleLines(975, 40, 295, y - 50, WHITE);					//Prawe menu
	drawInputs(1165, 50, 95, 30, WHITE);
	drawButtons(985, 50, 170, 30, WHITE);
}

//void Graphics::prepareButtons() {
//
//}

void Graphics::drawButtons(int startX, int startY, int width, int height, Color color) const {
	bRegen.draw(startX, startY, width, height, color, "Reg. podloza");
	bHunger.draw(startX, startY + 40, width, height, color, "Odpornosc na glod");
	bSize.draw(startX, startY + 80, width, height, color, "Maks. wielkosc");
	bLifespan.draw(startX, startY + 120, width, height, color, "Sr. czas zycia");
	bChildren.draw(startX, startY + 160, width, height, color, "Ilosc mlodych");
	bProductivity.draw(startX, startY + 200, width, height, color, "Sr. czas prod.");
}

void Graphics::drawInputs(int startX, int startY, int width, int height, Color color) const {
	for (Input input : inputs) {
		input.draw(startX, startY, width, height, color);
		startY += 40;
	}
}

void Graphics::drawWormBox() const {
	DrawRectangleLines(295, 40, y - 50, y - 50, RED);
}

void Graphics::checkInput() {
	//bRegen
	//if(manager.isMouseOver())
	//
}

void Graphics::end() const {
	EndDrawing();
}