#pragma once
#include "Button.h"
#include "Input.h"
#include "InputManager.h"
#include "Simulation.h"
#include <vector>
#include <string>
#include "Worm.h"

class Graphics {
	int x, y;
	InputManager manager;
	Simulation simulation;
	std::vector<Button> buttons;
	std::vector<Input> inputs;
	std::vector<std::vector<int>> tiles;
	void drawMenu();
	void drawWormBox() const;
	void drawWorm();
	void generateWormBoxRandom();
	void generateWormBoxHotspot();
	void drawWorm(int x, int y, int size) const;
	void drawTiles(int width, int height, int size) const;
	void prepareButtons(int startX, int startY, int width, int height);
	void prepareInputs(int startX, int startY, int width, int height);
	void drawButtons();
	void drawInputs();
public:
	Graphics(Simulation& simulation, int x = 1280, int y = 720);
	void begin() const;
	void end() const;
	void draw();
};

