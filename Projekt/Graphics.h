#pragma once
#include "Button.h"
#include "Input.h"
#include "InputManager.h"
#include <vector>
#include <string>

class Graphics {
	int x, y;
	InputManager manager;
	std::vector<Button> buttons;
	std::vector<Input> inputs;
	void drawMenu() const;
	void drawWormBox() const;
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

