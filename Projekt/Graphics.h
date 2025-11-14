#pragma once
#include "Button.h"
#include "Input.h"
#include "InputManager.h"
#include "Simulation.h"
#include <vector>
#include <string>

class Graphics {
	int x, y;
	InputManager manager;
	Simulation simulation;
	std::vector<Button> buttons;
	std::vector<Input> inputs;
	std::vector<std::vector<int>> tiles;
	void drawMenu();
	void drawWormBox() const;
	void generateWormBoxRandom();
	void generateWormBoxHotspot();
	void drawTiles(int width, int height, int size) const;
	void prepareButtons(int startX, int startY, int width, int height);
	void prepareInputs(int startX, int startY, int width, int height);
	void drawButtons(InputManager manager);
	void drawInputs(InputManager manager);
public:
	Graphics(int x = 1280, int y = 720);
	void begin() const;
	void end() const;
	void draw();
};

