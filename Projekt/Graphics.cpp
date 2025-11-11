#include "Graphics.h"
#include "Button.h"
#include "raylib.h"
#include <vector>

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
	//DrawRectangleLines(10, 40, x - 20, y - 50, WHITE); //width = 1260; height = 670
	drawMenu();
	drawWormBox();
}

void Graphics::drawMenu() const {
	DrawRectangleLines(10, 40, 275, y - 50, WHITE);						//Lewe menu ?????
	DrawRectangleLines(975, 40, 275, y - 50, WHITE);					//Prawe menu
	
	//Draw buttons

}

void Graphics::drawWormBox() const {
	DrawRectangleLines(295, 40, y - 50, y - 50, RED);
}

void Graphics::end() const {
	EndDrawing();
}