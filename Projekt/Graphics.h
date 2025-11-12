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
	std::vector<std::vector<Tile>> tiles;
	void drawMenu() const;
	void drawWormBox() const;
	void generateWormBox();
	void prepareButtons(int startX, int startY, int width, int height);
	void prepareInputs(int startX, int startY, int width, int height);
	void drawButtons(InputManager manager) const;
	void drawInputs(InputManager manager) const;
public:
	Graphics(int x = 1280, int y = 720);
	void begin() const;
	void end() const;
	void draw() const;
};

